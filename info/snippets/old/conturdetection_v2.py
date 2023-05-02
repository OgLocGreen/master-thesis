import cv2
import numpy as np

# Load the image
image = cv2.imread('panorama.png')

# Check if the image was loaded successfully
if image is None:
    print("Error: Failed to load the image.")
    exit()

# Convert the image to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Apply image thresholding
_, thresh = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY)

# Find contours in the image
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Create an empty mask for the result
mask = np.zeros_like(image)

# Define an area threshold to remove small contours (adjustable)
min_area = 1000

# Create an empty list to store grouped contours
grouped_contours = []

# Iterate over all found contours
for contour in contours:
    # Calculate the perimeter of the contour
    perimeter = cv2.arcLength(contour, True)

    # Approximate the contour to a closed contour with fewer corners
    epsilon = 0.02 * perimeter
    approx = cv2.approxPolyDP(contour, epsilon, True)

    # Calculate the area of the contour
    area = cv2.contourArea(contour)

    # Filter out contours with small area (e.g. text)
    if area >= min_area and len(approx) >= 3:
        # Draw the contour in white on the mask
        cv2.drawContours(mask, [contour], 0, (255, 255, 255), -1)

        # Add the contour to the grouped contours list
        grouped_contours.append(contour)

# Save the result image
cv2.imwrite("contours.jpg", mask)

# Create an empty mask for the result
mask_only_hull = np.zeros_like(image)

# Number the grouped contours
for i in range(len(grouped_contours)):
    # Calculate the centroid of the contour
    M = cv2.moments(grouped_contours[i])
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])

    # Convert the contour to a closed line
    hull = cv2.convexHull(grouped_contours[i])
    cv2.drawContours(mask, [hull], 0, (0, 0, 255), 2)
    cv2.drawContours(mask_only_hull, [hull], 0, (0, 0, 255), 4)

# Save the result image
cv2.imwrite("closed_contours.jpg", mask)

# Save the result image
cv2.imwrite("only_closed_contours.jpg", mask_only_hull)