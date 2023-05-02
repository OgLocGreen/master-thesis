import cv2
import numpy as np
# Load the image
image = cv2.imread('closed_contours.png', cv2.IMREAD_GRAYSCALE)

# Define the kernel (structuring element) for dilation
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (20, 1)) # 1x5 rectangular kernel for left dilation

# Perform dilation on the image
dilated_image = cv2.dilate(image, kernel, iterations=2)


# Display the original and dilated images
cv2.imshow('Original Image', image)
cv2.imshow('Dilated Image (Left)', dilated_image)
cv2.waitKey(0)
cv2.destroyAllWindows()