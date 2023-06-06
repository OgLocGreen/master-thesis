import cv2
import numpy as np

# Create a black image with a red square
image = np.zeros((400, 400, 3), dtype=np.uint8)
image[100:300, 100:300, :] = (0, 0, 255)  # Red square

image = cv2.imread("./panorama.png")

# Define the rotation angle
angle = 30

# Get the rotation matrix
center = (image.shape[1] // 2, image.shape[0] // 2)  # Calculate the center point
rotation_matrix = cv2.getRotationMatrix2D(center, angle, 1.0)


# Calculate the new image size
cos_theta = np.abs(rotation_matrix[0, 0])
sin_theta = np.abs(rotation_matrix[0, 1])
new_width = int((image.shape[1] * cos_theta) + (image.shape[0] * sin_theta))
new_height = int((image.shape[1] * sin_theta) + (image.shape[0] * cos_theta))

# Adjust the translation component of the matrix to center the rotated image
rotation_matrix[0, 2] += (new_width / 2) - center[0]
rotation_matrix[1, 2] += (new_height / 2) - center[1]

# Apply the rotation to the image
rotated_image = cv2.warpAffine(image, rotation_matrix, (new_width, new_height))

# Display the original and rotated images
cv2.imshow("Original Image", image)
cv2.imshow("Rotated Image", rotated_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
