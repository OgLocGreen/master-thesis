import cv2
import numpy as np

# Load the image
img = cv2.imread('your_image.jpg')

# Convert the image to grayscale
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Apply thresholding to convert the image to binary
ret, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

# Find the contours in the image
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Create an empty array to hold the polygonal approximations of the contours
polygons = []

# Loop over the contours
for i in range(len(contours)):
    # Approximate the contour with a polygon of desired level of detail
    epsilon = 0.01 * cv2.arcLength(contours[i], True) # You can adjust this value to change the level of detail
    approx = cv2.approxPolyDP(contours[i], epsilon, True)
    
    # Add the polygon to the list of polygons
    polygons.append(approx)

# Draw the closed polygons on the original image
for poly in polygons:
    cv2.drawContours(img, [poly], 0, (0, 0, 255), 2)


# Display the image
cv2.imshow('image', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
