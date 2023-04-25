import cv2
import numpy as np
# Load the image
image = cv2.imread('hull_only.png', cv2.IMREAD_GRAYSCALE)

# Define the kernel (structuring element) for dilation
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (100, 1)) # 1x5 rectangular kernel for left dilation

# Perform dilation on the image
dilated_image = cv2.dilate(image, kernel, iterations=1)


# Find contours in the dilated image
contours, hierarchy = cv2.findContours(dilated_image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Create an empty mask for the result
mask_only_hull = np.zeros_like(image)

# Draw convex hulls around the contours
for contour in contours:
    hull = cv2.convexHull(contour)
    cv2.drawContours(mask_only_hull, [hull], 0, (0, 0, 255), 2)

# Display the original and dilated images
cv2.imshow('Original Image', image)
cv2.imshow('Dilated Image (Left)', dilated_image)
cv2.imshow('Original Image with Contours', mask_only_hull)
cv2.waitKey(0)
cv2.destroyAllWindows()