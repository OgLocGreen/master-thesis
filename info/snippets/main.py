
import numpy as np
import cv2
import matplotlib.pyplot as plt

import snippets.ComputerVision as cvh
import WorkingZones as wz
import PathPlanning as pp

if __name__ == "__main__":
  # Load shape

    P = cv2.imread("./snippets/images/panorama_border.png", cv2.IMREAD_GRAYSCALE)


    # Perform convex hull operation
    P = wz.convex_hull_image(P)

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
    P = wz.resizePlate(P, W_P, L_P, bs)
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

    T_roff = wz.toolFootprint(t_y, t_x, L_T, alpha_T)



    angStep = 45  # angular steps in degrees
    angPose = np.arange(0, 360, angStep)  # possible angular values
    brakeDistance = 20
    
    RT_fp = wz.strelUnion(R_rct, T_roff)
    size_P = np.array(P.shape)
    length_angPose = len(angPose)

    I_2 = np.zeros(np.concatenate((size_P, [length_angPose])), dtype=np.uint8)
    I_20 = np.zeros(np.concatenate((size_P, [length_angPose])), dtype=np.uint8)

        
    for k in range(len(angPose)):
        RTfp, Tfp, RTfpb0 = wz.rotateRobotTool(R_rct, T_roff, angPose[k], brakeDistance)
        A, A_0 = wz.safeAreaRobot(P, RTfp, Tfp)
        I_2[:, :, k] = A
        I_20[:, :, k] = A_0
    border_size = 100

    for zoneNum in range(1, 6):

        objZone = wz.AnalysisRegion(zonesName, zoneNum)

        indexSequence, sectionSequence, nonInspectZones, test = wz.solveSetCovering(objZone, I_2, 0)
        print(indexSequence)


        for index in indexSequence:
            print(angPose[index])
        # loop over the images in test
        for i, img in enumerate(test):
            # normalize the image to be between 0 and 255
            img_normalized = cv2.normalize(img, None, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8U)
            image_A_no_border = img_normalized[border_size:-border_size, border_size:-border_size]
            cv2.imwrite("./snippets/images/image_"+str(zoneNum)+"_"+str(i)+"_"+str(angPose[indexSequence[i]])+".png", image_A_no_border)






    