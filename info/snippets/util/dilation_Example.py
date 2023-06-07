import cv2
import numpy as np

# Create a binary image with a square shape
image = np.zeros((200, 200), dtype=np.uint8)
image[100:200, 100:200] = 255

# Define the desired padding size
padding_size = 3

# Add padding to the image
padded_image = cv2.copyMakeBorder(image, padding_size, padding_size, padding_size, padding_size, cv2.BORDER_CONSTANT, value=0)

# Define the structuring element
kernel = np.ones((3, 3), dtype=np.uint8)

# Perform dilation on the padded image
dilated_image = cv2.dilate(padded_image, kernel, iterations=1)
dilated_image_2 = cv2.dilate(image, kernel, iterations=1)
# Remove the padding from the dilated image
result = dilated_image[padding_size:-padding_size, padding_size:-padding_size]

# Display the results
cv2.imshow('Original Image', image)
cv2.imshow('Padded Image', padded_image)
cv2.imshow('Dilated Image', dilated_image)
cv2.imshow('Dilated Image_2', dilated_image_2)
cv2.imshow('Result', result)
cv2.waitKey(0)
cv2.destroyAllWindows()
