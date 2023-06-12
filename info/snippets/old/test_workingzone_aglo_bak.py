import cv2
import numpy as np
from skimage.morphology import convex_hull_image


import matplotlib.pyplot as plt
from scipy.ndimage import  binary_dilation
from scipy.ndimage import binary_erosion
from scipy.ndimage import rotate

def resizePlate(P, W_P, L_P, bs):
    # Get the bounding box
    contours, _ = cv2.findContours(P.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    x, y, w, h = cv2.boundingRect(contours[0])

    # Crop the image
    P = P[y:y+h, x:x+w]

    # Resize image
    P = cv2.resize(P.astype(np.uint8), (L_P, W_P))

    # Pad the resulting image
    P = cv2.copyMakeBorder(P, bs, bs, bs, bs, cv2.BORDER_CONSTANT, value=0)

    return P

def robotFootprint(W_R, L_R):
    # Create a rectangle shape with specified width and length
    R_rct = np.ones((W_R, L_R), dtype=np.uint8)

    return R_rct

def toolFootprint(t_y, t_x, L_T, alpha_T):


    # Step 1: Mark the position of the tool/sensor center
    # This works for 90 degrees only
    T_off = np.zeros((2 * int(t_y) + 1, 2 * int(t_x) + 1), dtype=np.uint8)
    T_off[0, 2 * int(t_x)] = 1
    line = np.ones((1, L_T), dtype=np.uint8)
    line_reshaped = line
    # This T_roff_1 only works for 90,180,270 degrees
    # Reshape the line vector based on the angle
    if alpha_T == 0:
        line_reshaped = line.reshape(-1, 1)  # Keep it as a column vector
    elif alpha_T == 90:
        line_reshaped = line.reshape(1, -1)  # Keep it as a row vector
    elif alpha_T == 180:
        line_reshaped = np.flip(line).reshape(-1, 1)  # Flip and make it a column vector
    elif alpha_T == 270:
        line_reshaped = np.flip(line).reshape(1, -1)  # Flip and make it a row vector
    T_roff_1 = cv2.dilate(T_off, line_reshaped, iterations=1)



    # works for any angles but when 90 degrees does have a 0 at the first place
    # FIXME: why is there a 0 in the first place (first row)? in the line_angle
    # FIXME: also does not work for angle 180
    # FIXME: also for angle > 90, the footprint miss a 1 in the first row


    # Define the desired padding size
    padding_size = int(L_T/2)

    # Add padding to the image
    T_off_padded = cv2.copyMakeBorder(T_off, padding_size, padding_size, padding_size, padding_size, cv2.BORDER_CONSTANT, value=0)

    #make the line 
    line = np.ones((1, L_T), dtype=np.uint8)
    center = (line.shape[1]/ 2, line.shape[0]/ 2)
    rotation_matrix=  cv2.getRotationMatrix2D(center, alpha_T, 1.0)
    # Calculate the new image size
    cos_theta = np.abs(rotation_matrix[0, 0])
    sin_theta = np.abs(rotation_matrix[0, 1])
    new_width = int((line.shape[1] * cos_theta) + (line.shape[0] * sin_theta))
    new_height = int((line.shape[1] * sin_theta) + (line.shape[0] * cos_theta))
    # Adjust the translation component of the matrix to center the rotated image
    rotation_matrix[0, 2] += (new_width / 2) - center[0]
    rotation_matrix[1, 2] += (new_height / 2) - center[1]
    # Rotate the robot footprint in X direction by the specified robotPose angle
    line_angle = cv2.warpAffine(line.astype(np.uint8), rotation_matrix, (new_width, new_height))
    T_roff_2 = cv2.dilate(T_off_padded, line_angle, iterations=1)



    # Trying to fix the problem with the 0 in the first row
    if alpha_T == 90:
        line_angle[0] = 1
    T_roff_3 = cv2.dilate(T_off, line_angle, iterations=1)


    #TODO: in matlab its 109x119 logical
    # in python its (89, 119) T_roff_2
    # the dilate is not working properly
    # it only add its to the picture
    # but it should make it bigger

    # Fix: i need to padd it first
    # so i make it bigger but i dont know on whiche side so i make it all bigger
    # does it matter if the footprint is bigger?
    # i mean there are just zeros
    # this is t_roff_2

    #TODO: in matlab its directly on the corner here its in the middle
    # i think it doesnt bother because the rest are zeros

    plt.subplot(1,4,1)
    plt.imshow(T_off,  cmap='gray')
    plt.title('T_off')

    plt.subplot(1,4,2)
    plt.imshow(T_roff_1)
    plt.title('T_roff_1')

    plt.subplot(1,4,3)
    plt.imshow(T_roff_2)
    plt.title('T_roff_2')

    plt.subplot(1,4,4)
    plt.imshow(T_roff_3)
    plt.title('T_roff_3')

    # Adjust the spacing between subplots
    plt.tight_layout()

    # Show the figure
    plt.show()

    return T_off, T_roff_1, T_roff_2, T_roff_3

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

    A_0 = binary_erosion(np.uint8(P), np.uint8(R_rct))

    # Also compute the area covered by the tool/sensor when the robot stays
    # within A_0. It is computed as the dilation of A_0 by T_roff. T_roff is
    # the footprint covered by the tool/sensor. The origin of this footprint is
    # the centre of the robot.
    
    A = binary_dilation(np.uint8(A_0), np.uint8(T_roff))

    """
    plt.imshow(A_0, cmap='gray')
    plt.title('A_0')
    plt.show()   
    plt.imshow(A, cmap='gray')
    plt.title('A')
    plt.show()
    plt.imshow(P, cmap='gray')
    plt.title('P')
    plt.show()
    plt.imshow(R_rct, cmap='gray')
    plt.title('R_rct')
    plt.show()  
    """

    return A, A_0


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

    #Rotate
    R_rct_roteted = rotate(R_rct.astype(np.uint8), robotPose, reshape=True)

    # make a struct elemten out of it
    Rfpb0 = R_rct_roteted

    structuring_element_scipy = np.ones((2 * brakeDistance + 1, 1), dtype=np.uint8)
    Rfp = binary_dilation(R_rct.astype(np.uint8), structuring_element_scipy)

    Rfp = rotate(Rfp, robotPose, reshape=True)
    
    Tfp = rotate(T_roff.astype(np.uint8), robotPose, reshape=True)

    #TODO: check if this is correct
    """
    plt.imshow(R_rct.astype(np.uint8), cmap='gray')
    plt.title("R_rct")
    plt.show()
    plt.imshow(Rfpb0, cmap='gray')
    plt.title("Rfpb0")
    plt.show()
    plt.imshow(Rfp, cmap='gray')
    plt.title("Rfp")
    plt.show()
    plt.imshow(Tfp, cmap='gray')
    plt.title("Tfp")
    plt.show()
    """

    return Rfp, Tfp, Rfpb0

def rotateRobotTool(R_rct, T_roff, robotPose, brakeDistance):  

    # Compute RTfpb0
    Rfp, Tfp, RTfpb0 = rotateRobot(R_rct, T_roff, robotPose, brakeDistance)

    # Perform the union of the binary images
    R_rct = cv2.resize(R_rct.astype(np.uint8), (T_roff.shape[1], T_roff.shape[0]))
    RTfp_binary = cv2.bitwise_or(R_rct.astype(np.uint8), T_roff.astype(np.uint8))

    # Create a new structuring element RTfp based on the binary union result
    RTfp = cv2.getStructuringElement(cv2.MORPH_RECT, RTfp_binary.shape)

    line_structuring_element = cv2.getStructuringElement(cv2.MORPH_RECT, (1, brakeDistance))


    # Perform dilation on RTfp.Neighborhood using the line-shaped structuring element
    dilated_neighborhood = cv2.dilate(RTfp.astype(np.uint8), line_structuring_element, iterations=1)

    # Create the structuring element RTfp based on the dilated result
    RTfp = cv2.getStructuringElement(cv2.MORPH_RECT, dilated_neighborhood.shape)


    RTfp, Tfp, _ = rotateRobot(RTfp, T_roff, robotPose)
    """
    # Compute RTfpb0
    Rfp, Tfp, RTfpb0 = rotateRobot(R_rct, T_roff, robotPose, brakeDistance)

    #RTfp = strelUnion(R_rct, T_roff)
    R_rct = cv2.resize(R_rct.astype(np.uint8), (T_roff.shape[1], T_roff.shape[0]))
    RTfp = cv2.bitwise_or(R_rct.astype(np.uint8), T_roff.astype(np.uint8))
    structuring_element_scipy = np.ones((2 * brakeDistance + 1, 1), dtype=np.uint8)
    RTfp = binary_dilation(RTfp.astype(np.uint8), structuring_element_scipy)
    RTfp, Tfp, Rfpb0 = rotateRobot(RTfp, T_roff, robotPose)
    """ 
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


def drawSchematic(P, A_0, A, Rfp, Tfp, Rbfp=None):
    plt.clf()
    robot , _ = cv2.findContours(Rfp.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    robot = robot[0]
    rc = np.mean(robot, axis=0)

    # x coloms
    # y rows
    # functions return x,y "normaly"
    # matlab returns row, col so y,x
    # check whats happening in matlab
    

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

    data = plate
    x = data[:, 0, 0]
    y = data[:, 0, 1]
    x = np.append(x, x[0])
    y = np.append(y, y[0])
    plt.plot(x,y, 'b')

    plt.gca().invert_yaxis()
    plt.axis('equal')


    data = A_0edge
    x = data[:, 0, 0]
    y = data[:, 0, 1]
    x = np.append(x, x[0])
    y = np.append(y, y[0])
    plt.plot(x, y, 'm--')

    data = A_edge
    x = data[:, 0, 0]
    y = data[:, 0, 1]
    x = np.append(x, x[0])
    y = np.append(y, y[0])
    plt.plot(x,y, 'k-.')

    for k in range(0, extrema.shape[0]):
        x = robot[:, 0, 0]+ extrema[k, 1]
        y = robot[:, 0, 1]+ extrema[k, 0]
        x = np.append(x, x[0])
        y = np.append(y, y[0])
        plt.plot(x,y, 'g')
        plt.plot(extrema[k, 1] + ct, extrema[k, 0] + rt, 'ks')
        
        #FIXME: Works more or less but the lines have some offset
        # i think its because of rounding problems
        plt.plot(extrema[k, 1], extrema[k, 0], 'go')


    if Rbfp is not None:
        robotb, _ = cv2.findContours(Rbfp.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        rcb = np.array(Rbfp.shape) / 2
        for k in range(extrema.shape[0]):
            for l in range(len(robotb)):
                shape = robotb[l] - rcb
                plt.plot(shape[1] + extrema[k, 1], shape[0] + extrema[k, 0], 'g--')


    plt.legend(["plate", "Robot safe area", "Inspected area", "robot", "tool/Sensor"])
    plt.show()
    print("done")


def strelUnion_bak(S1, S2):
    m1, n1 = S1.shape
    m2, n2 = S2.shape

    m = max(m1, m2)
    n = max(n1, n2)

    # Pad S1
    if m1 < m:
        pad_height = (m - m1) // 2
        S1 = np.pad(S1, [(pad_height, pad_height), (0, 0)])
    if n1 < n:
        pad_width = (n - n1) // 2
        S1 = np.pad(S1, [(0, 0), (pad_width, pad_width)])

    # Pad S2
    if m2 < m:
        pad_height = (m - m2) // 2
        S2 = np.pad(S2, [(pad_height, pad_height), (0, 0)])
    if n2 < n:
        pad_width = (n - n2) // 2
        S2 = np.pad(S2, [(0, 0), (pad_width, pad_width)])

    S_union = binary_erosion(S1.astype(np.uint8), S2.astype(np.uint8))
    #TODO: Check if the S_union is correct
    return S_union

def strelUnion(array1, array2):
    if array1.shape > array2.shape:
        pass
    elif array2.shape > array1.shape:
        array1, array2 = array2, array1

    # Calculate the starting position for placing the square in the middle
    start_x = (array1.shape[0] - array2.shape[0]) // 2
    start_y = (array1.shape[1] - array2.shape[1]) // 2

    # Create an array with the square placed in the middle
    expanded_array2 = np.zeros_like(array1, dtype=bool)
    expanded_array2[start_x:start_x+array2.shape[0], start_y:start_y+array2.shape[1]] = True

    # Perform element-wise logical OR operation
    result = np.logical_or(array1, expanded_array2)
    return result


def paddedErosion(A, SE):
    m = np.ceil(SE.shape[0] / 2).astype(int)
    n = np.ceil(SE.shape[1] / 2).astype(int)

    A = A.astype(bool)
    SE = SE.astype(bool)
    A_padded = np.pad(A, ((m, m), (n, n)), mode='constant', constant_values=0)
    I = binary_erosion(A_padded.astype(np.uint8), SE.astype(np.uint8))
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
    P = resizePlate(P, W_P, L_P, bs);

    # Find the edge boundaries
    contours, _ = cv2.findContours(P, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    Pedge = contours[0]

    # Display the image with the edge boundaries
    plt.imshow(P, cmap='gray')
    plt.plot(Pedge[:, :, 0], Pedge[:, :, 1], 'r--', linewidth=2)
    plt.show()


    # Define robot size
    L_R = 75   #1 pixel = 1 cm
    W_R = 65

    # Define robot footprint
    R_rct = np.ones((W_R, L_R), dtype=bool)

    # Display the robot footprint
    plt.imshow(R_rct, cmap='gray')
    plt.axis('on')
    plt.show()



    # Define sensor footprint size and offset
    L_T = 21  # 1 pixel = 1 cm
    W_T = 5
    alpha_T = 90  # In degrees
    t_x = np.ceil(L_R/2) + 21  # 11
    t_y = np.ceil(W_R/2) + 11  # 5

    T_roff , T_roff_1 ,  T_roff_2 , T_roff_3 = toolFootprint(t_y, t_x, L_T, alpha_T)
    
    # Set the last column of the first 21 rows to 1
    #TODO: make this automaticly
    array = np.zeros((109, 119))
    array[:21, -1] = 1
    T_roff = T_roff_2

    plt.imshow(T_roff, cmap='gray')
    plt.axis('on')
    plt.title('Tool footprint')
    plt.show()



    # Call the safeAreaRobot function
    A, A_0 = safeAreaRobot(P, R_rct, T_roff)

    # Concatenate the arrays along the third dimension
    combined = np.dstack((P, A_0, A))
    # Convert the combined array to uint8 data type
    combined = combined.astype(np.uint8)
    # Scale the values by 255
    scaled = combined * 255
    # Display the image using Matplotlib
    plt.imshow(scaled)
    plt.show()

    drawSchematic(P, A_0, A, R_rct, T_roff)

    # robot orientation in degrees
    alpha_R = -30
    Rfp, Tfp, Rfpb0 = rotateRobot(R_rct, T_roff, alpha_R)
    A, A_0 = safeAreaRobot(P, Rfp, Tfp)

    # Concatenate the arrays along the third dimension
    combined = np.dstack((P, A_0, A))
    # Convert the combined array to uint8 data type
    combined = combined.astype(np.uint8)
    # Scale the values by 255
    scaled = combined * 255
    # Display the image using Matplotlib
    plt.imshow(scaled)
    plt.show()
    drawSchematic(P, A_0, A, Rfp, Tfp, Rfpb0)



    robotPose = 180
    brakeDistance = 20

    RTfp, Tfp, RTb0fp = rotateRobotTool(R_rct, T_roff, robotPose, brakeDistance)
    A, A_0 = safeAreaRobot(P, RTfp, Tfp)

    drawSchematic(P, A_0, A, RTfp, Tfp, RTb0fp)


    angStep = 45  # angular steps in degrees
    angPose = np.arange(0, 360, angStep)  # possible angular values

    brakeDistance = 20
    robotPose = -30
    RT_fp = strelUnion(R_rct, T_roff)

    plt.imshow(RT_fp, cmap='gray')
    plt.axis('on')
    plt.title('Union of the robot and tool footprints')
    plt.show()

    RTfp, Tfp, RTb0fp = rotateRobotTool(RT_fp, T_roff, robotPose, brakeDistance)
    A, A_0 = safeAreaRobot(P, RTfp, Tfp)
    drawSchematic(P, A_0, A, RTfp, Tfp, RTb0fp)



    size_P = np.array(P.shape)
    length_angPose = len(angPose)

    I_2 = np.zeros(np.concatenate((size_P, [length_angPose])), dtype=np.uint8)
    I_20 = np.zeros(np.concatenate((size_P, [length_angPose])), dtype=np.uint8)

    for k in range(len(angPose)):
        RTfp, Tfp, RTfpb0 = rotateRobotTool(R_rct, T_roff, angPose[k], brakeDistance)
        A, A_0 = safeAreaRobot(P, RTfp, Tfp)
        I_2[:, :, k] = A
        I_20[:, :, k] = A_0

    I_any = np.any(I_2, axis=2)
    plt.imshow(I_any)
    plt.show()
    
    I_sum = np.sum(I_2, axis=2)
    plt.imshow(I_sum)
    plt.show()

    I = np.any(I_2, axis=2)
    I = I.astype(np.uint8)*255
    plt.imshow(I)
    data = Pedge
    x = data[:, 0, 0]
    y = data[:, 0, 1]
    x = np.append(x, x[0])
    y = np.append(y, y[0])
    plt.plot(x, y, 'r--', linewidth=2)
    plt.show()


    NI = P & (~I)
    plt.imshow(NI)
    plt.plot(x, y, 'r--', linewidth=2)
    plt.show()

    zoneNum = 0
    objZone = AnalysisRegion(zonesName, zoneNum)

    indexSequence, sectionSequence, nonInspectZones = solveSetCovering(objZone, I_2, 0)

    plt.imshow(sectionSequence)
    plt.show()

    zoneNum = 1
    objZone = AnalysisRegion(zonesName, zoneNum)

    indexSequence, sectionSequence, nonInspectZones = solveSetCovering(objZone, I_2, 0)

    plt.imshow(sectionSequence)
    plt.show()


    zoneNum = 2
    objZone = AnalysisRegion(zonesName, zoneNum)

    indexSequence, sectionSequence, nonInspectZones = solveSetCovering(objZone, I_2, 0)

    plt.imshow(sectionSequence)
    plt.show()






    print("done")