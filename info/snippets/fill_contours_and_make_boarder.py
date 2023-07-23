import cv2
import numpy as np
import os

# Load shape
image = cv2.imread("./snippets/panorama_hulls.png", cv2.IMREAD_GRAYSCALE)


# Find contours in the image
contours, _ = cv2.findContours(image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Get the shape of the original image
height, width = image.shape

white_image = np.ones((height, width, 3), dtype=np.uint8) * 255

# Fill the contours with red color
for cnt in contours:
    #cv2.drawContours(image, [cnt], 0, (0, 0, 255), 1)  # (0, 0, 255) is the BGR value for red
    cv2.drawContours(white_image, contours, -1, color=(255, 0, 0), thickness=cv2.FILLED)

image_A = white_image

# Get the shape of the original image
height, width,channel = image_A.shape

# Create a new white image with the same size as the original image
image_B = np.ones((height, width, 3), dtype=np.uint8) * 255

# Add a black border around the image
border_size = 100
image_B = cv2.copyMakeBorder(image_B, border_size, border_size, border_size, border_size, cv2.BORDER_CONSTANT, value=[0, 0, 0])
image_A = cv2.copyMakeBorder(image_A, border_size, border_size, border_size, border_size, cv2.BORDER_CONSTANT, value=[0, 0, 0])


# The border was added symmetrically, so the same value should be removed from all sides
image_A_no_border = image_A[border_size:-border_size, border_size:-border_size]



cv2.imshow("image_A", image_A)
cv2.waitKey(0)


cv2.imshow("image_B", image_B)
cv2.waitKey(0)

cv2.imshow("image_A_no_border", image_A_no_border)
cv2.waitKey(0)

cv2.destroyAllWindows()



cv2.imwrite("./snippets/panorama_hulls_filled.png", image_A)
cv2.imwrite("./snippets/panorama_hulls_filled_border.png", image_B)