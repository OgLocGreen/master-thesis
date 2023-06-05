import cv2
import numpy as np
from skimage.morphology import convex_hull_image
from skimage.morphology import binary_erosion, binary_dilation
from skimage.measure import find_contours
from skimage.measure import regionprops

from scipy.ndimage import morphology, rotate
import matplotlib.pyplot as plt


def resizePlate(P, W_P, L_P, bs):
    # Get the bounding box
    contours, _ = cv2.findContours(P.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    x, y, w, h = cv2.boundingRect(contours[0])

    # Crop the image
    P = P[y:y+h, x:x+w]

    # Resize image
    P = cv2.resize(P, (L_P, W_P))

    # Pad the resulting image
    P = cv2.copyMakeBorder(P, bs, bs, bs, bs, cv2.BORDER_CONSTANT, value=0)

    return P

def robotFootprint(W_R, L_R):
    # Create a rectangle shape with specified width and length
    R_rct = np.ones((W_R, L_R), dtype=np.uint8)

    return R_rct

def toolFootprint(t_y, t_x, L_T, alpha_T):
    # Define sensor footprint center position
    T_off = np.zeros((2*int(t_y)+1, 2*int(t_x)+1), dtype=np.uint8)
    T_off[0, 2*int(t_x)] = 1

    # Define shape of the footprint
    T_rct = cv2.getStructuringElement(cv2.MORPH_RECT, (L_T, 1))
    T_rct = cv2.rotate(T_rct, alpha_T)

    # Translate the footprint based on the position of its center
    T_roff = cv2.dilate(T_off, T_rct)

    return T_roff

def AnalysisRegion(imageName, zoneNum):
    # Read the image and convert it to HSV color space
    plateZones = cv2.imread(imageName)
    plateZones = cv2.cvtColor(plateZones, cv2.COLOR_BGR2HSV)

    # Extract the saturation channel and perform thresholding
    _, saturation, _ = cv2.split(plateZones)
    _, binary = cv2.threshold(saturation, 0.8 * 255, 255, cv2.THRESH_BINARY)

    # Apply connected component labeling to identify distinct zones
    numLabels, labeledImage = cv2.connectedComponents(binary)

    # Compute the result for the specified zone number
    objZone = np.uint8(labeledImage == zoneNum)

    return objZone


def safeAreaRobot(P, R_rct, T_roff):
    # Compute in A_0 the area on the plate that can be traversed by the robot
    # without leaving the plate. This is the result of eroding P with R_rct.
    # P is the footprint of the confined area (the plate) that can not be
    # left by the robot. R_rct is the footprint of the robot that can not
    # leave the area P due to safety reasons. R_rct includes the robot itself
    # and any other sensor/tool that may protrude from the robot. The origin is
    # placed at the robot centre.
    
    A_0 = cv2.erode(np.uint8(P), np.uint8(R_rct))
    #A_0 = binary_erosion(P, structure=R_rct)    

    # Also compute the area covered by the tool/sensor when the robot stays
    # within A_0. It is computed as the dilation of A_0 by T_roff. T_roff is
    # the footprint covered by the tool/sensor. The origin of this footprint is
    # the centre of the robot.
    
    A = cv2.dilate(np.uint8(A_0), np.uint8(T_roff))
    #A = binary_dilation(A_0, structure=T_roff)

    return A, A_0


from scipy.ndimage.morphology import binary_dilation
from skimage.transform import rotate

def rotateRobot(R_rct, T_roff, robotPose, brakeDistance=0):
    # Compute robot and tool/sensor footprint when the robot is rotated alpha_R
    # degrees with respect to plate X axis. A positive angle means a ccw rotation.
    # This function should be used when the tool/sensor is allowed to move
    # outside the confinement area.

    # INPUT:
    # R_rct -> robot footprint for robot pose 0 degrees.
    # T_roff -> tool/sensor footprint 
    # robotPose -> the orientation of the robot with respect to the confinement
    #              region X axis. Positive values represent ccw rotation
    # brakeDistance -> this is the distance, in pixels, that the robot needs to
    #                  stop (or to get desired speed when initial speed is 0).

    # OUTPUT:
    # Rfp -> The robot footprint increased, in the movement direction, by the 
    #        distance needed to stop and rotated to face in the direction
    #        indicated by robotPose.
    # Tfp -> The tool/sensor footprint allowed to move outside of the
    #        confinement region, rotated the same amount as the robot.
    # Rfpb0 -> robot footprint rotated, but without considering the braking
    #          distance

    if brakeDistance is None:
        brakeDistance = 0

    # Rotate the robot footprint without considering the braking distance
    Rfpb0 = rotate(R_rct, robotPose, mode='constant')

    # Create a binary structuring element for dilation
    structuring_element = [[0, 1, 0]]

    # Dilate the robot footprint in the X direction by the amount specified in brakeDistance
    #Rfp = binary_dilation(R_rct, structure=structuring_element, iterations=brakeDistance)
    Rfp = cv2.dilate(np.uint8(R_rct), np.uint8(structuring_element), iterations=brakeDistance)

    # Rotate the resulting footprint
    Rfp = rotate(Rfp, robotPose, mode='constant')

    # Rotate the tool/sensor footprint
    Tfp = rotate(T_roff, robotPose, mode='constant')

    return Rfp, Tfp, Rfpb0

def rotateRobotTool(R_rct, T_roff, robotPose, brakeDistance):
    # Compute RTfpb0
    RTfpb0 = rotateRobot(R_rct, T_roff, robotPose, brakeDistance)

    # Convert the images to the appropriate data type
    R_rct = R_rct.astype(np.uint8)
    T_roff = T_roff.astype(np.uint8)

    # Resize the images to have the same shape
    R_rct_resized = cv2.resize(R_rct, T_roff.shape[::-1])
    T_roff_resized = T_roff

    # Perform bitwise OR operation
    RTfp = cv2.bitwise_or(R_rct_resized, T_roff_resized)
    se = np.ones((2 * brakeDistance + 1, 1))
    RTfp = morphology.binary_dilation(RTfp, se)

    # Compute Tfp
    RTfp, Tfp, _ = rotateRobot(RTfp, T_roff, robotPose)

    return RTfp, Tfp, RTfpb0


def solveSetCovering(pendingZone, accessibility, minflag=True):
    # Solve the set covering problem based on a pending zone and accessibility information.

    if minflag is None:
        minflag = True

    # Compute nonInspectZones: the set of points in the object zone that cannot be accessed with any robot orientation.
    nonInspectZones = pendingZone & (~np.any(accessibility, axis=2))

    # Compute the zone that will be inspected.
    pendingZone = pendingZone & (~nonInspectZones)

    # Compute the area that has not been covered yet.
    pendingArea = np.sum(pendingZone)

    # Use the zone to be inspected as a mask to remove accessible points in
    # accessibility outside the zone of interest.
    accessibility = accessibility * pendingZone[:,:,np.newaxis]

    # Initialize output variables
    indexSequence = []
    inspectSequence = np.zeros_like(accessibility[:,:,0], dtype=np.uint8)

    k = 0

    # While there are points to be inspected
    while (pendingArea > 0):
        # Compute how many poses allow reaching each point in the remaining area
        numPoses = np.sum(accessibility, axis=2)

        if minflag:
            # Find the minimum value bigger than zero
            np_min = np.min(numPoses[numPoses > 0])

            # Generate a mask with the detected locations
            mask = (numPoses == np_min)
        else:
            mask = pendingZone

        # For each orientation that allows covering at least a point in the mask,
        # compute the area that can be inspected
        areabypose = np.sum(accessibility, axis=(0, 1))
        validposes = np.any(accessibility & mask[:,:,np.newaxis], axis=(0, 1))
        c = areabypose * validposes

        # Find the maximum valid area and its position
        nextPose = np.argmax(c)
        cNext = c[nextPose]
        indexSequence.append(nextPose)
        pendingArea -= cNext
        pendingZone = pendingZone & (~accessibility[:,:,nextPose])
        k += 1
        inspectSequence += k * np.uint8(accessibility[:,:,nextPose])
        accessibility = accessibility & (~accessibility[:,:,nextPose][:,:,np.newaxis])

    return indexSequence, inspectSequence, nonInspectZones

def computeCurrentCost2(accessibility, mask):
    # Initialize the area for each orientation as zero
    c = np.zeros(accessibility.shape[2])

    # For each possible orientation
    for k in range(accessibility.shape[2]):
        # Compute the cost for the current orientation
        c[k] = np.any(accessibility[:,:,k] & mask) * np.sum(accessibility[:,:,k])

    return c


def drawSchematic_bak(P, A_0, A, Rfp, Tfp, Rbfp=None):
    # Extract boundaries
    robot = find_contours(Rfp)
    rc = np.mean(robot, axis=0)
    robot = robot - rc
    plate = find_contours(P, 0.5)[0]
    A_0edge = find_contours(A_0, 0.5)[0]

    extrema = regionprops(A_0)["extrema"]
    extrema = np.unique(extrema[:, [1, 0]], axis=0)

    A_edge = find_contours(A, 0.5)[0]
    rt, ct = np.where(Tfp.Neighborhood)

    rt = rt - np.ceil(Tfp.Neighborhood.shape[0] / 2)
    ct = ct - np.ceil(Tfp.Neighborhood.shape[1] / 2)

    # Plotting
    plt.figure()
    plt.plot(plate[:, 1], plate[:, 0])
    plt.gca().invert_yaxis()
    plt.axis("equal")
    plt.hold(True)
    plt.plot(A_0edge[:, 1], A_0edge[:, 0], 'm--')
    plt.plot(A_edge[:, 1], A_edge[:, 0], 'k-.')

    plt.plot(robot[:, 1] + extrema[0, 1], robot[:, 0] + extrema[0, 0], 'g')
    plt.plot(ct + extrema[0, 1], rt + extrema[0, 0], 'kx')
    plt.plot(extrema[0, 1], extrema[0, 0], 'go')

    for k in range(1, extrema.shape[0]):
        plt.plot(robot[:, 1] + extrema[k, 1], robot[:, 0] + extrema[k, 0], 'g')
        plt.plot(ct + extrema[k, 1], rt + extrema[k, 0], 'ks')
        plt.plot(extrema[k, 1], extrema[k, 0], 'go')

    if Rbfp is not None:
        robotb = find_contours(Rbfp.Neighborhood, 0.5)
        rcb = np.array(Rbfp.Neighborhood.shape) / 2
        for k in range(extrema.shape[0]):
            for l in range(len(robotb)):
                shape = robotb[l] - rcb
                plt.plot(shape[:, 1] + extrema[k, 1], shape[:, 0] + extrema[k, 0], 'g--')

    plt.legend(["plate", "Robot safe area", "Inspected area", "robot", "tool/Sensor"])
    plt.hold(False)
    plt.show()

def drawSchematic_bak(P, A_0, A, Rfp, Tfp, Rbfp=None):
    cv2.imshow("P", Rfp.astype(np.uint8) * 255)

    robot, _ = cv2.findContours(Rfp.astype(np.uint8)*255, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    robot = robot[0]
    rc = np.mean(robot, axis=0)
    robot = robot - rc

    plate, _ = cv2.findContours(P.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    plate = plate[0]

    A_0edge, _ = cv2.findContours(A_0.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    A_0edge = A_0edge[0]

    extrema = cv2.findContours(A_0.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
    extrema = np.unique(extrema.reshape(-1, 2)[:, ::-1], axis=0)

    A_edge, _ = cv2.findContours(A.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    A_edge = A_edge[0]

    rt, ct = np.where(Tfp.Neighborhood)
    rt = rt - int(Tfp.Neighborhood.shape[0] / 2)
    ct = ct - int(Tfp.Neighborhood.shape[1] / 2)

    plt.plot(plate[:, :, 1], plate[:, :, 0])
    plt.gca().invert_yaxis()
    plt.axis('equal')
    plt.hold(True)
    plt.plot(A_0edge[:, :, 1], A_0edge[:, :, 0], 'm--')
    plt.plot(A_edge[:, :, 1], A_edge[:, :, 0], 'k-.')
    plt.plot(robot[:, :, 1] + extrema[0, 1], robot[:, :, 0] + extrema[0, 0], 'g')
    plt.plot(ct + extrema[0, 1], rt + extrema[0, 0], 'kx')
    plt.plot(extrema[0, 1], extrema[0, 0], 'go')

    for k in range(1, extrema.shape[0]):
        plt.plot(robot[:, :, 1] + extrema[k, 1], robot[:, :, 0] + extrema[k, 0], 'g')
        plt.plot(ct + extrema[k, 1], rt + extrema[k, 0], 'ks')
        plt.plot(extrema[k, 1], extrema[k, 0], 'go')

    if Rbfp is not None:
        robotb, _ = cv2.findContours(Rbfp.Neighborhood.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        rcb = np.array(Rbfp.Neighborhood.shape) / 2
        for k in range(extrema.shape[0]):
            for l in range(len(robotb)):
                shape = robotb[l] - rcb
                plt.plot(shape[:, :, 1] + extrema[k, 1], shape[:, :, 0] + extrema[k, 0], 'g--')

    plt.legend(["plate", "Robot safe area", "Inspected area", "robot", "tool/Sensor"])
    plt.hold(False)
    plt.show()


def drawSchematic(P, A_0, A, Rfp, Tfp, Rbfp=None):
    new = Rfp.astype(np.uint8)
    cv2.imshow("new_255", new)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    robot , _ = cv2.findContours(Rfp.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    robot = robot[0]


    rc = np.mean(robot, axis=0)
    robot = robot - rc

    plate, _  = cv2.findContours(P.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    plate = plate[0]

    A_0edge , _ = cv2.findContours(A_0.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    A_0edge = A_0edge[0]

    extrema = cv2.findContours(A_0.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
    extrema = np.unique(extrema[0].reshape(-1, 2)[:, ::-1], axis=0)

    A_edge, _ = cv2.findContours(A.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    A_edge = A_edge[0]

    rt, ct = np.where(Tfp)
    rt = rt - int(Tfp.shape[0] / 2)
    ct = ct - int(Tfp.shape[1] / 2)

    #plt.plot(plate[:, :, 1], plate[:, :, 0])
    plt.plot(plate[1], plate[0])

    plt.gca().invert_yaxis()
    plt.axis('equal')
    plt.show()
    points = A_0edge
    # Reshape the points array to (N, 2)
    points = points.reshape(-1, 2)

    # Extract x and y coordinates from the points array
    x = points[:, 0]
    y = points[:, 1]

    # Connect the last point with the first point
    x = np.append(x, x[0])
    y = np.append(y, y[0])


    # Plot the lines between points
    plt.plot(x, y, 'b-')

    # Show the plot
    plt.show()
    
    #TODO: do it like this above it should work


    plt.plot(A_0edge[1], A_0edge[0], 'm--')
    plt.plot(A_edge[1], A_edge[0], 'k-.')
    plt.plot(robot[1] + extrema[0, 1], robot[0] + extrema[0, 0], 'g')
    plt.plot(ct + extrema[0, 1], rt + extrema[0, 0], 'kx')
    plt.plot(extrema[0, 1], extrema[0, 0], 'go')

    for k in range(1, extrema.shape[0]):
        plt.plot(robot[1] + extrema[k, 1], robot[0] + extrema[k, 0], 'g')
        plt.plot(ct + extrema[k, 1], rt + extrema[k, 0], 'ks')
        plt.plot(extrema[k, 1], extrema[k, 0], 'go')

    if Rbfp is not None:
        _, robotb, _ = cv2.findContours(Rbfp.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        rcb = np.array(Rbfp.shape) / 2
        for k in range(extrema.shape[0]):
            for l in range(len(robotb)):
                shape = robotb[l] - rcb
                plt.plot(shape[1] + extrema[k, 1], shape[0] + extrema[k, 0], 'g--')

    plt.legend(["plate", "Robot safe area", "Inspected area", "robot", "tool/Sensor"])

    plt.show()

def strelUnion(S1, S2):
    S1 = S1.astype(bool)
    S2 = S2.astype(bool)

    m1, n1 = S1.shape
    m2, n2 = S2.shape

    m = max(m1, m2)
    n = max(n1, n2)

    # pad S1
    if m1 < m:
        S1 = np.pad(S1, ((m-m1)//2, 0))
    if n1 < n:
        S1 = np.pad(S1, ((0, 0), (n-n1)//2))

    # pad S2
    if m2 < m:
        S2 = np.pad(S2, ((m-m2)//2, 0))
    if n2 < n:
        S2 = np.pad(S2, ((0, 0), (n-n2)//2))

    S = np.logical_or(S1, S2)
    return S


def paddedErosion(A, SE):
    m = np.ceil(SE.shape[0] / 2).astype(int)
    n = np.ceil(SE.shape[1] / 2).astype(int)

    A = A.astype(bool)
    SE = SE.astype(bool)

    I = binary_erosion(np.pad(A, ((m, m), (n, n))), SE)
    I = I[m:-m, n:-n]
    return I


def blobOrientation(BW):
    # compute the area M00 = u00
    area = np.sum(BW)

    # compute the central moments of order 2
    # 1. compute points coordinates
    y, x = np.where(BW)
    # 2. compute the centre coordinates (M10, M01)
    centre = np.mean([x, y], axis=1)
    # 3. refer the coordinates to the blob centre
    points = np.column_stack((x, y)) - centre
    # 4. Compute u20, u02, u11
    u20 = np.sum(points[:, 0] ** 2)
    u02 = np.sum(points[:, 1] ** 2)
    u11 = np.sum(points[:, 0] * points[:, 1])

    # Compute the eigenvalues
    D = np.sqrt((u20 - u02) ** 2 + 4 * u11 ** 2)
    # bigger eigenvalue
    a = (u20 + u02 + D) / 2
    # smaller eigenvalue
    b = (u20 + u02 - D) / 2

    # Compute the orientation
    theta = np.arctan2(2 * u11, u20 - u02) / 2 * 180 / np.pi

    return theta, a, b, centre, area

if __name__ == "__main__":

    # Load shape
    P = cv2.imread("./info/snippets/chapaRectangEscalada.png", cv2.IMREAD_GRAYSCALE)

    # Perform convex hull operation
    P = convex_hull_image(P)

    # Display the resulting image or perform further operations



    zonesName = "./info/snippets/chapaRectangEscaladaZonas.png"

    # Define bounding box dimensions (1 pixel = 1 cm)
    L_P = 701
    W_P = 301
    bs = 100

    # Resize the plate
    P_resized = cv2.resize(P.astype(np.uint8), (L_P, W_P))

    # Find the edge boundaries
    contours, _ = cv2.findContours(P_resized, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    Pedge = contours[0]

    # Display the image with the edge boundaries
    plt.imshow(P_resized, cmap='gray')
    plt.plot(Pedge[:, :, 0], Pedge[:, :, 1], 'r--', linewidth=2)
    plt.show()


    # Define robot size
    L_R = 75  # 1 pixel = 1 cm
    W_R = 65

    # Define robot footprint
    R_rct = np.ones((W_R, L_R), dtype=bool)

    # Display the robot footprint
    plt.imshow(R_rct, cmap='gray')
    plt.axis('on')
    plt.show()



    # Define sensor footprint size and offset
    L_T = 21  # 1 pixel = 1 cm
    W_T = 1
    alpha_T = 90  # In degrees
    t_x = np.ceil(L_R/2) + 21  # 11
    t_y = np.ceil(W_R/2) + 11  # 5

    T_roff = toolFootprint(t_y, t_x, L_T, alpha_T)

    cv2.imshow("Tool Footprint", T_roff)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


    # Call the safeAreaRobot function
    A, A_0 = safeAreaRobot(P, R_rct, T_roff)

    # Display the images
    images = np.concatenate((P[:, :, np.newaxis], A_0[:, :, np.newaxis], A[:, :, np.newaxis]), axis=2)
    cv2.imshow("Images", images * 255)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    #TODO: Till here it works

    drawSchematic(P, A, A_0, R_rct, T_roff)


    robotPose = 180
    brakeDistance = 20

    RTfp, Tfp, RTb0fp = rotateRobotTool(R_rct, T_roff, robotPose, brakeDistance)
    A, A_0 = safeAreaRobot(P, RTfp, Tfp)

    drawSchematic(P, A_0, A, RTfp, Tfp, RTb0fp)

    plt.show()
    print("Done")