import numpy as np
from skimage.draw import line
import cv2
import matplotlib.pyplot as plt

def toolFootprint(t_y, t_x, L_T, alpha_T):


    # Step 1: Mark the position of the tool/sensor center
    # This works for 90 degrees only
    T_off = np.zeros((2 * t_y + 1, 2 * t_x + 1), dtype=np.uint8)
    T_off[0, 2 * t_x] = 1
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


# Example usage
t_y = 44
t_x = 59
L_T = 20
alpha_T = 10

T_roff = toolFootprint(t_y, t_x, L_T, alpha_T)

for i in range(360):
    if i % 90 == 0:
        print(i)
        plt.suptitle(i)
        T_roff = toolFootprint(t_y, t_x, L_T, i)
    if i == 30:
        print(i)
        plt.suptitle(i)
        T_roff = toolFootprint(t_y, t_x, L_T, i)
    if i == 45:
        print(i)
        plt.suptitle(i)
        T_roff = toolFootprint(t_y, t_x, L_T, i)
    if i == 110:
        print(i)
        plt.suptitle(i)
        T_roff = toolFootprint(t_y, t_x, L_T, i)
    if i == 200:
        print(i)
        plt.suptitle(i)
        T_roff = toolFootprint(t_y, t_x, L_T, i)