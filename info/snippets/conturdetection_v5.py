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

# Create an empty mask for the result
mask_only_hull = np.zeros_like(image)

# Number the grouped hull contours
hull_goup = []

# Number the grouped contours
for i in range(len(grouped_contours)):
    # Calculate the centroid of the contour
    M = cv2.moments(grouped_contours[i])
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])

    # Convert the contour to a closed line
    hull = cv2.convexHull(grouped_contours[i])
    hull_goup.append(hull)

# Draw the new convex hull on a black image
image_with_hull = np.zeros_like(image)

for hull in hull_goup:
    
    
    # Extract the edges from the convex hull
    edges = []
    for i in range(len(hull) - 1):
        edges.append((tuple(hull[i][0]), tuple(hull[i + 1][0])))
    edges.append((tuple(hull[-1][0]), tuple(hull[0][0])))


    # Define the threshold distance to the image border
    threshold = 50

    # Update vertices of edges close to the border
    for i, edge in enumerate(edges):
        updated_edge = []
        for vertex in edge:
            x, y = vertex
            if x < threshold:
                x = 0
            elif x >= image.shape[1] - threshold:
                x = image.shape[1] - 1
            if y < threshold:
                y = 0
            elif y >= image.shape[0] - threshold:
                y = image.shape[0] - 1
            updated_edge.append((x, y))
        edges[i] = tuple(updated_edge)

    # Create a new convex hull from the updated edges
    hull_from_edges = cv2.convexHull(np.array(edges).reshape(-1, 2), clockwise=False)

    cv2.drawContours(image_with_hull, [hull_from_edges], 0, 255, -1)

# Show the original image, the edges, and the image with the new hull
cv2.imshow("Original Image", image)
cv2.imshow("Image with Hull", image_with_hull)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Save the result image
cv2.imwrite("closed_contours.png", mask)
cv2.imwrite("hull_only.png", mask_only_hull)

# Display the result image Image mask_only_hull
cv2.imshow('mask_only_hull', mask_only_hull)

# Create an empty mask for the result
mask_only_hull_with_border = np.zeros_like(image)

