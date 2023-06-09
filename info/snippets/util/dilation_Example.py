import cv2
import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage import binary_dilation
from skimage.morphology import dilation


def perform_binary_dilation(image, brake_distance):
    # pad the picture to make it bigger so the dilation can be made
    # Numpy
    image_pad = np.pad(image, brake_distance, mode='constant', constant_values=0)

    # OpenCV
    pad_size = brake_distance //2
    image_pad_2 = cv2.copyMakeBorder(image, pad_size, pad_size, pad_size, pad_size, cv2.BORDER_CONSTANT, value=0)
    image_pad = image_pad_2

    # Do the dilation
    # OpenCV
    structuring_element_opencv = cv2.getStructuringElement(cv2.MORPH_RECT, (2 * brake_distance + 1, 2 * brake_distance + 1))
    dilated_image_opencv = cv2.dilate(image_pad, structuring_element_opencv)

    # SciPy
    structuring_element_scipy = np.ones((2 * brake_distance + 1, 2 * brake_distance + 1), dtype=np.uint8)
    dilated_image_scipy = binary_dilation(image_pad, structure=structuring_element_scipy)

    # scikit-image
    structuring_element_skimage = np.ones((2 * brake_distance + 1, 2 * brake_distance + 1), dtype=np.uint8)
    dilated_image_skimage = dilation(image_pad, footprint=structuring_element_skimage)

    # Displaying the results
    titles = ['Original Image',"Image padded", 'OpenCV', 'SciPy', 'scikit-image']
    images = [image, image_pad, dilated_image_opencv,  dilated_image_scipy, dilated_image_skimage]
    

    plt.figure(figsize=(12, 6))
    for i, (title, img) in enumerate(zip(titles, images)):
        plt.subplot(2, 3, i+1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('on')
        print(title, img.shape)
    plt.tight_layout()
    plt.show()

import cv2
import numpy as np
from scipy.ndimage import binary_erosion
from skimage.morphology import erosion


def perform_binary_erosion(image, brake_distance):
    # OpenCV
    structuring_element_opencv = cv2.getStructuringElement(cv2.MORPH_RECT, (2 * brake_distance + 1, 2 * brake_distance + 1))
    eroded_image_opencv = cv2.erode(image, structuring_element_opencv)

    # SciPy
    structuring_element_scipy = np.ones((2 * brake_distance + 1, 2 * brake_distance + 1), dtype=np.uint8)
    eroded_image_scipy = binary_erosion(image, structure=structuring_element_scipy)

    # scikit-image
    structuring_element_skimage = np.ones((2 * brake_distance + 1, 2 * brake_distance + 1), dtype=np.uint8)
    eroded_image_skimage = erosion(image, footprint=structuring_element_skimage)

    # Displaying the results
    titles = ['Original Image', 'OpenCV', 'SciPy', 'scikit-image']
    images = [image, eroded_image_opencv, eroded_image_scipy, eroded_image_skimage]

    plt.figure(figsize=(12, 6))
    for i, (title, img) in enumerate(zip(titles, images)):
        plt.subplot(2, 3, i+1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('on')
        print(title, img.shape)
    plt.tight_layout()
    plt.show()

import cv2
import numpy as np
from scipy.ndimage import rotate
from skimage.transform import rotate as skimage_rotate

def perform_rotation(image, angle):
    # OpenCV
    rotated_image_opencv = cv2.rotate(image, cv2.ROTATE_90_CLOCKWISE)

    # SciPy
    rotated_image_numpy_scipy = rotate(image, angle, reshape=False)

    # scikit-image
    rotated_image_skimage = skimage_rotate(image, angle)

    # Displaying the results
    titles = ['Original Image', 'OpenCV', 'SciPy', 'scikit-image']
    images = [image, rotated_image_opencv, rotated_image_numpy_scipy, rotated_image_skimage]

    plt.figure(figsize=(12, 6))
    for i, (title, img) in enumerate(zip(titles, images)):
        plt.subplot(2, 3, i+1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('on')
        print(title, img.shape)
    plt.tight_layout()
    plt.show()

def perform_rotation_sizing(image, angle):
    # OpenCV

    center = (image.shape[1]/ 2, image.shape[0]/ 2) 
    rotation_matrix=  cv2.getRotationMatrix2D(center, angle, 1.0)
    # Calculate the new image size
    cos_theta = np.abs(rotation_matrix[0, 0])
    sin_theta = np.abs(rotation_matrix[0, 1])
    new_width = int((image.shape[1] * cos_theta) + (image.shape[0] * sin_theta))
    new_height = int((image.shape[1] * sin_theta) + (image.shape[0] * cos_theta))
    # Adjust the translation component of the matrix to center the rotated image
    rotation_matrix[0, 2] += (new_width / 2) - center[0]
    rotation_matrix[1, 2] += (new_height / 2) - center[1]
    # Rotate the robot footprint in X direction by the specified robotPose angle
    rotated_image_opencv = cv2.warpAffine(image.astype(np.uint8), rotation_matrix, (new_width, new_height))

    # SciPy
    rotated_image_numpy_scipy = rotate(image, angle, reshape=True)

    # scikit-image
    rotated_image_skimage = skimage_rotate(image, angle, resize=True)

    # Displaying the results
    titles = ['Original Image', 'OpenCV', 'SciPy', 'scikit-image']
    images = [image, rotated_image_opencv, rotated_image_numpy_scipy, rotated_image_skimage]

    plt.figure(figsize=(12, 6))
    for i, (title, img) in enumerate(zip(titles, images)):
        plt.subplot(2, 3, i+1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('on')
        print(title, img.shape)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    image = np.zeros((500, 500), dtype=np.uint8)  # Creating a black image of size 500x500
    red_square = np.ones((200, 200), dtype=np.uint8) * 255  # Creating a white square of size 200x200

    brake_distance = 50

    # Placing the red square in the middle of the image
    start_x = (image.shape[0] - red_square.shape[0]) // 2
    start_y = (image.shape[1] - red_square.shape[1]) // 2
    image[start_x:start_x + red_square.shape[0], start_y:start_y + red_square.shape[1]] = red_square

    perform_binary_dilation(image, brake_distance)

    # Placing the square in the corner of the image
    image = np.zeros((500, 500), dtype=np.uint8)  # Creating a black image of size 500x500
    start_x = image.shape[0] - red_square.shape[0]
    start_y = image.shape[1] - red_square.shape[1] 
    image[start_x:start_x + red_square.shape[0], start_y:start_y + red_square.shape[1]] = red_square

    perform_binary_dilation(image, brake_distance)


    perform_binary_erosion(image, brake_distance)


    # Placing the red square in the middle of the image
    image = np.zeros((500, 500), dtype=np.uint8)  # Creating a black image of size 500x500
    red_square = np.ones((200, 200), dtype=np.uint8) * 255  # Creating a white square of size 200x200
    start_x = (image.shape[0] - red_square.shape[0]) // 2
    start_y = (image.shape[1] - red_square.shape[1]) // 2
    image[start_x:start_x + red_square.shape[0], start_y:start_y + red_square.shape[1]] = red_square

    perform_rotation(image, 45)


    image = np.zeros((500, 500), dtype=np.uint8)  # Creating a black image of size 500x500
    red_square = np.ones((500, 500), dtype=np.uint8) * 255  # Creating a white square of size 200x200
    start_x = (image.shape[0] - red_square.shape[0]) // 2
    start_y = (image.shape[1] - red_square.shape[1]) // 2
    image[start_x:start_x + red_square.shape[0], start_y:start_y + red_square.shape[1]] = red_square

    perform_rotation(image, 45)
    perform_rotation_sizing(image, 45)


    #TODO: Überprüfen ob die Struktuellen elemente gleich gemacht werden wie in matlab
    #TODO: dann überprüfen welche der Funktionen wir am besten verweden
    #TODO: dann die Funktionen in die test.py einbauen und noch mal überprüfen


    cv2.waitKey(0)
    cv2.destroyAllWindows()