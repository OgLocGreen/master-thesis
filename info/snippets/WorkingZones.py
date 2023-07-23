import cv2
import numpy as np
from skimage.morphology import convex_hull_image

import matplotlib.pyplot as plt
from scipy.ndimage import  binary_dilation
from scipy.ndimage import binary_erosion
from scipy.ndimage import rotate

def resizePlate(P, W_P, L_P, bs):
    """
    Resizes and pads a given image.
    
    This function crops an image to its bounding box, resizes it to a specified width and length, and then adds a padding border of a specified size around it.

    Args:
        P (numpy.ndarray): Input image.
        W_P (int): Desired width of the resized image.
        L_P (int): Desired length of the resized image.
        bs (int): Border size for padding.

    Returns:
        P (numpy.ndarray): Output image which is resized and padded.
    """
    
    # Find contours in the image to get the bounding box
    contours, _ = cv2.findContours(P.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    x, y, w, h = cv2.boundingRect(contours[0])

    # Crop the image to the bounding box
    P = P[y:y+h, x:x+w]

    # Resize the cropped image to the desired dimensions
    P = cv2.resize(P.astype(np.uint8), (L_P, W_P))

    # Add padding to the resized image
    P = cv2.copyMakeBorder(P, bs, bs, bs, bs, cv2.BORDER_CONSTANT, value=0)

    return P

def robotFootprint(W_R, L_R):
    """
    Creates a binary image representing the footprint of a robot.
    
    This function creates a binary image (represented as a NumPy array) in the shape of a rectangle with specified width and length, filled with ones. This can represent a "footprint" of a robot on a grid map.

    Args:
        W_R (int): Width of the robot footprint rectangle.
        L_R (int): Length of the robot footprint rectangle.

    Returns:
        R_rct (numpy.ndarray): Binary image of the robot footprint.
    """

    # Create a binary image in the shape of a rectangle
    R_rct = np.ones((W_R, L_R), dtype=np.uint8)

    return R_rct

def toolFootprint(t_y, t_x, L_T, alpha_T):
    """
    Generates the footprint of a tool or sensor at a given position and orientation.
    
    Args:
        t_y (float): Y-coordinate of the tool/sensor center.
        t_x (float): X-coordinate of the tool/sensor center.
        L_T (int): Length of the tool/sensor footprint.
        alpha_T (int): Angle of rotation for the tool/sensor footprint.

    Returns:
        T_roff (numpy.ndarray): Binary image of the tool/sensor footprint (works for any angle, with some limitations).
    """

    # Step 1: Mark the position of the tool/sensor center
    T_off = np.zeros((2 * int(t_y) + 1, 2 * int(t_x) + 1), dtype=np.uint8)
    T_off[0, 2 * int(t_x)] = 1

    line = np.ones((1, L_T), dtype=np.uint8)

    padding_size = int(L_T / 2)

    # Add padding to the tool/sensor center image
    T_off_padded = cv2.copyMakeBorder(T_off, padding_size, padding_size, padding_size, padding_size, cv2.BORDER_CONSTANT, value=0)

    center = (line.shape[1] / 2, line.shape[0] / 2)

    # Rotate the line to match the desired angle
    rotation_matrix = cv2.getRotationMatrix2D(center, alpha_T, 1.0)
    cos_theta = np.abs(rotation_matrix[0, 0])
    sin_theta = np.abs(rotation_matrix[0, 1])
    new_width = int((line.shape[1] * cos_theta) + (line.shape[0] * sin_theta))
    new_height = int((line.shape[1] * sin_theta) + (line.shape[0] * cos_theta))
    rotation_matrix[0, 2] += (new_width / 2) - center[0]
    rotation_matrix[1, 2] += (new_height / 2) - center[1]

    # Rotate the padded tool/sensor center image to generate the footprint for any angle
    line_angle = cv2.warpAffine(line.astype(np.uint8), rotation_matrix, (new_width, new_height))
    T_off = cv2.dilate(T_off_padded, line_angle, iterations=1)

    return T_off

def AnalysisRegion(imageName, zoneNum):
    """
    Analyzes a specific region within an image based on zone number.
    
    Args:
        imageName (str): The name of the image file.
        zoneNum (int): The zone number to analyze.
    
    Returns:
        objZone (numpy.ndarray): Binary image representing the specified zone.
    """
    
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
    """
    Computes the safe area for the robot and the area covered by the tool/sensor.
    
    This function computes the area on the plate that can be traversed by the robot without leaving the plate, and the area covered by the tool/sensor when the robot stays within that safe area. The safe area is computed by eroding P (the confined area) with R_rct (the robot footprint). The covered area is computed by dilating the safe area with T_roff (the tool/sensor footprint).
    
    Args:
        P (numpy.ndarray): Footprint of the confined area (plate).
        R_rct (numpy.ndarray): Footprint of the robot including any protruding sensors/tools.
        T_roff (numpy.ndarray): Footprint covered by the tool/sensor.
    
    Returns:
        A (numpy.ndarray): Area covered by the tool/sensor within the safe area.
        A_0 (numpy.ndarray): Safe area that can be traversed by the robot without leaving the plate.
    """
    
    # Compute the safe area (A_0) by eroding P with R_rct
    A_0 = binary_erosion(np.uint8(P), np.uint8(R_rct))

    # Compute the area covered by the tool/sensor (A) by dilating A_0 with T_roff
    A = binary_dilation(np.uint8(A_0), np.uint8(T_roff))

    return A, A_0

def rotateRobot(R_rct, T_roff, robotPose, brakeDistance=0):
    """
    Rotates the robot and tool/sensor footprints based on the robot's pose.
    
    This function rotates the robot and tool/sensor footprints by the specified angle (robotPose) with respect to the confinement region's X axis. It also takes into account the brake distance for the robot.
    
    Args:
        R_rct (numpy.ndarray): Robot footprint for robot pose at 0 degrees.
        T_roff (numpy.ndarray): Tool/sensor footprint.
        robotPose (float): The orientation of the robot with respect to the confinement region's X axis. Positive values represent a counterclockwise rotation.
        brakeDistance (int, optional): The distance, in pixels, that the robot needs to stop or get the desired speed when the initial speed is 0.
    
    Returns:
        Rfp (numpy.ndarray): The robot footprint increased, in the movement direction, by the distance needed to stop and rotated to face in the direction indicated by robotPose.
        Tfp (numpy.ndarray): The tool/sensor footprint allowed to move outside of the confinement region, rotated the same amount as the robot.
        Rfpb0 (numpy.ndarray): Robot footprint rotated, but without considering the braking distance.
    """
    
    if brakeDistance is None:
        brakeDistance = 0

    # Rotate the robot footprint by the robotPose angle
    R_rct_rotated = rotate(R_rct.astype(np.uint8), robotPose, reshape=True)

    # Create a structuring element based on the brake distance
    structuring_element_scipy = np.ones((2 * brakeDistance + 1, 1), dtype=np.uint8)

    # Dilate the robot footprint to account for the braking distance
    Rfpb0 = R_rct_rotated

    Rfp = binary_dilation(R_rct.astype(np.uint8), structuring_element_scipy)
    Rfp = rotate(Rfp, robotPose, reshape=True)

    Tfp = rotate(T_roff.astype(np.uint8), robotPose, reshape=True)

    # Display the images (uncomment if necessary)
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
    """
    Rotates the robot and tool/sensor footprints, considering the braking distance.
    
    This function rotates the robot footprint and tool/sensor footprint based on the specified robot pose and braking distance. The rotated footprints are returned along with the rotated robot footprint without considering the braking distance.
    
    Args:
        R_rct (numpy.ndarray): Robot footprint for robot pose at 0 degrees.
        T_roff (numpy.ndarray): Tool/sensor footprint.
        robotPose (float): The orientation of the robot with respect to the confinement region's X axis. Positive values represent a counterclockwise rotation.
        brakeDistance (int): The distance, in pixels, that the robot needs to stop or get the desired speed when the initial speed is 0.
    
    Returns:
        RTfp (numpy.ndarray): The robot footprint increased, in the movement direction, by the distance needed to stop and rotated to face in the direction indicated by robotPose.
        Tfp (numpy.ndarray): The tool/sensor footprint allowed to move outside of the confinement region, rotated the same amount as the robot.
        RTfpb0 (numpy.ndarray): Robot footprint rotated, but without considering the braking distance.
    """
    
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

    # Rotate RTfp, Tfp, and Rfpb0
    RTfp, Tfp, _ = rotateRobot(RTfp, T_roff, robotPose)
    
    return RTfp, Tfp, RTfpb0

def solveSetCovering(pendingZone, accessibility, minflag=True):
    """
    Solves the set covering problem based on a pending zone and accessibility information.
    
    This function solves the set covering problem using the pending zone and accessibility information. It returns the index sequence, inspect sequence, and non-inspected zones.
    
    Args:
        pendingZone (numpy.ndarray): Binary image representing the pending zone.
        accessibility (numpy.ndarray): Accessibility information.
        minflag (bool, optional): Flag to indicate whether to use the minimum value (default: True).
    
    Returns:
        indexSequence (list): Index sequence.
        inspectSequence (numpy.ndarray): Inspect sequence.
        nonInspectZones (numpy.ndarray): Non-inspected zones.
    """
    
    if minflag is None:
        minflag = True

    # Compute nonInspectZones: the set of points in the object zone that cannot be accessed with any robot orientation.



    nonInspectZones = pendingZone & (~np.any(accessibility, axis=2))

    # Compute the zone that will be inspected.
    pendingZone = pendingZone & (~nonInspectZones)

    # Compute the area that has not been covered yet.
    pendingArea = np.sum(pendingZone)

    # Use the zone to be inspected as a mask to remove accessible points in accessibility outside the zone of interest.
    accessibility = accessibility * pendingZone[:,:,np.newaxis]

    # Initialize output variables
    indexSequence = []
    inspectSequence = np.zeros_like(accessibility[:,:,0], dtype=np.uint8)

    test = []

    k = 0

    # While there are points to be inspected
    while (pendingArea > 0):
        """
        plt.imshow(pendingZone.astype(np.uint8)*255)
        plt.title("pendingZone")
        plt.axis('on')
        plt.show()
        """
        # Compute how many poses allow reaching each point in the remaining area
        numPoses = np.sum(accessibility, axis=2)

        # If minflag is True, find the minimum value bigger than zero
        if minflag:
            np_min = np.min(numPoses[numPoses > 0])
            mask = (numPoses == np_min)  # Generate a mask with the detected locations
        else:
            mask = pendingZone

        # For each orientation that allows covering at least a point in the mask, compute the area that can be inspected
        areabypose = np.squeeze(np.sum(accessibility, axis=(0, 1)))
        validposes = np.squeeze(np.any(accessibility & accessibility & mask[:,:,np.newaxis], axis=(0, 1)))
        c = areabypose * validposes

        # Find the maximum valid area and its position
        nextPose = np.argmax(c)
        cNext = c[nextPose]
        indexSequence.append(nextPose)
        pendingArea -= cNext
        pendingZone = pendingZone & (~accessibility[:,:,nextPose])
        k += 1
        inspectSequence += k * np.uint8(accessibility[:,:,nextPose])
        test.append(k * np.uint8(accessibility[:,:,nextPose]))
        accessibility = accessibility & (~accessibility[:,:,nextPose][:,:,np.newaxis])

    return indexSequence, inspectSequence, nonInspectZones, test


def drawSchematic(P, A_0, A, Rfp, Tfp, Rbfp=None):
    """
    Draws the schematic representation of the plate, safe area, inspected area, robot, and tool/sensor.
    
    This function draws the schematic representation of the plate, safe area (A_0), inspected area (A), robot (Rfp), and tool/sensor (Tfp). Optionally, it can also draw the representation of the robot with braking distance (Rbfp).
    
    Args:
        P (numpy.ndarray): Footprint of the plate.
        A_0 (numpy.ndarray): Safe area that can be traversed by the robot.
        A (numpy.ndarray): Area covered by the tool/sensor within the safe area.
        Rfp (numpy.ndarray): Footprint of the robot.
        Tfp (numpy.ndarray): Footprint of the tool/sensor.
        Rbfp (numpy.ndarray, optional): Footprint of the robot with braking distance (default: None).
    """
    
    # Find the contours of the robot and calculate its centroid
    robot, _ = cv2.findContours(Rfp.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    robot = robot[0]
    rc = np.mean(robot, axis=0)

    # Subtract the centroid from the robot contours to center it
    robot = robot - rc

    # Find the contours of the plate
    plate, _ = cv2.findContours(P.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    plate = plate[0]

    # Find the contours of A_0
    A_0edge, _ = cv2.findContours(A_0.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    A_0edge = A_0edge[0]

    # Find the extrema points of A_0
    extrema = cv2.findContours(A_0.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
    extrema = np.unique(extrema[0].reshape(-1, 2)[:, ::-1], axis=0)

    # Find the contours of A
    A_edge, _ = cv2.findContours(A.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    A_edge = A_edge[0]

    # Compute the row and column indices of the tool/sensor footprint
    rt, ct = np.where(Tfp)
    rt = rt - int(Tfp.shape[0] / 2)
    ct = ct - int(Tfp.shape[1] / 2)

    # Plot the plate
    data = plate
    x = data[:, 0, 0]
    y = data[:, 0, 1]
    x = np.append(x, x[0])
    y = np.append(y, y[0])
    plt.plot(x, y, 'b')

    # Invert the y-axis and set equal aspect ratio
    plt.gca().invert_yaxis()
    plt.axis('equal')

    # Plot the safe area (A_0) as a dashed magenta line
    data = A_0edge
    x = data[:, 0, 0]
    y = data[:, 0, 1]
    x = np.append(x, x[0])
    y = np.append(y, y[0])
    plt.plot(x, y, 'm--')

    # Plot the inspected area (A) as a dotted black line
    data = A_edge
    x = data[:, 0, 0]
    y = data[:, 0, 1]
    x = np.append(x, x[0])
    y = np.append(y, y[0])
    plt.plot(x, y, 'k-.')

    # Plot the robot and its centroid
    for k in range(0, extrema.shape[0]):
        x = robot[:, 0, 0] + extrema[k, 1]
        y = robot[:, 0, 1] + extrema[k, 0]
        x = np.append(x, x[0])
        y = np.append(y, y[0])
        plt.plot(x, y, 'g')
        plt.plot(extrema[k, 1] + ct, extrema[k, 0] + rt, 'ks')

        #FIXME: Works more or less but the lines have some offset
        # i think its because of rounding problems
        plt.plot(extrema[k, 1], extrema[k, 0], 'go')

    # Plot the robot with braking distance (Rbfp) if provided
    if Rbfp is not None:
        robotb, _ = cv2.findContours(Rbfp.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        rcb = np.array(Rbfp.shape) / 2
        for k in range(extrema.shape[0]):
            for l in range(len(robotb)):
                shape = robotb[l] - rcb
                plt.plot(shape[1] + extrema[k, 1], shape[0] + extrema[k, 0], 'g--')

    # Add legend and display the plot
    plt.legend(["plate", "Robot safe area", "Inspected area", "robot", "tool/Sensor"])
    plt.show()
    print("done")


def strelUnion(array1, array2):
    """
    Computes the union of two arrays by expanding the smaller array to match the size of the larger array.

    Args:
        array1 (numpy.ndarray): First array.
        array2 (numpy.ndarray): Second array.

    Returns:
        result (numpy.ndarray): Union of the two arrays.
    """
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



if __name__ == "__main__":
    # Load shape

    P = cv2.imread("./snippets/images/panorama_border.png", cv2.IMREAD_GRAYSCALE)


    # Perform convex hull operation
    P = convex_hull_image(P)

    # Display the resulting image or perform further operations
    zonesName = "./snippets/images/panorama_hulls_filled.png"
    image = cv2.imread(zonesName)

    
    #plt.imshow(image, cmap='gray')
    #plt.axis('on')
    #plt.show()    

    print(P.shape)

    # Define bounding box dimensions (1 pixel = 1 cm)
    L_P = 1654
    W_P = 591
    bs = 100

        # Resize the plate
    P = resizePlate(P, W_P, L_P, bs)
    print(P.shape)
    # Display the robot footprint
    #plt.imshow(P, cmap='gray')
    #plt.axis('on')
    #plt.show()

    # Find the edge boundaries
    contours, _ = cv2.findContours(P, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    Pedge = contours[0]


    # Define robot size
    L_R = 75  # 1 pixel = 1 cm
    W_R = 58

    # Define robot footprint
    R_rct = np.ones((W_R, L_R), dtype=bool)

    # Border size
    border_size = 20

    # Create a new black image with the border size added
    new_image = np.zeros((W_R + 2*border_size, L_R + 2*border_size), dtype=np.uint8)

    # Add the original image to the center of the new image
    new_image[border_size:border_size+W_R, border_size:border_size+L_R] = R_rct


    # Define sensor footprint size and offset
    L_T = 20  # 1 pixel = 1 cm
    W_T = 10
    alpha_T = 90  # In degrees
    t_x = np.ceil(L_R/2) + L_T
    t_y = np.ceil(W_R/2) + W_T/2

    print("t_x: ", t_x)
    print("t_y: ", t_y)

    T_roff = toolFootprint(t_y, t_x, L_T, alpha_T)



    angStep = 45  # angular steps in degrees
    angPose = np.arange(0, 360, angStep)  # possible angular values
    brakeDistance = 20
    
    RT_fp = strelUnion(R_rct, T_roff)
    size_P = np.array(P.shape)
    length_angPose = len(angPose)

    I_2 = np.zeros(np.concatenate((size_P, [length_angPose])), dtype=np.uint8)
    I_20 = np.zeros(np.concatenate((size_P, [length_angPose])), dtype=np.uint8)

        
    for k in range(len(angPose)):
        RTfp, Tfp, RTfpb0 = rotateRobotTool(R_rct, T_roff, angPose[k], brakeDistance)
        A, A_0 = safeAreaRobot(P, RTfp, Tfp)
        I_2[:, :, k] = A
        I_20[:, :, k] = A_0
    border_size = 100

    for zoneNum in range(1, 6):

        objZone = AnalysisRegion(zonesName, zoneNum)

        indexSequence, sectionSequence, nonInspectZones, test = solveSetCovering(objZone, I_2, 0)
        print(indexSequence)


        for index in indexSequence:
            print(angPose[index])
        # loop over the images in test
        for i, img in enumerate(test):
            # normalize the image to be between 0 and 255
            img_normalized = cv2.normalize(img, None, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8U)
            image_A_no_border = img_normalized[border_size:-border_size, border_size:-border_size]
            cv2.imwrite("./snippets/images/image_"+str(zoneNum)+"_"+str(i)+"_"+str(angPose[indexSequence[i]])+".png", image_A_no_border)


    print("done")
