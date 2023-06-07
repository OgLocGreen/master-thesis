import cv2
import numpy as np

# Create a binary image
image = np.zeros((200, 200), dtype=np.uint8)
image[50:150, 50:150] = 255  # Add a white square in the center

# Create a kernel for erosion
kernel = np.ones((20, 20), dtype=np.uint8)

# Perform erosion on the image
eroded_image = cv2.erode(image, kernel, iterations=1)

# Display the original and eroded images
cv2.imshow('Original Image', image)
cv2.imshow('Eroded Image', eroded_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
