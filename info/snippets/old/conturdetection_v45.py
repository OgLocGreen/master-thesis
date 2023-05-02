import cv2
import numpy as np

# Load the image
image = cv2.imread('panorama.png')

#----------------------- get the Contours --------------------------------

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
img_contour = np.zeros_like(image)

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
        cv2.drawContours(img_contour, [contour], 0, (255, 255, 255), -1)

        # Add the contour to the grouped contours list
        grouped_contours.append(contour)


# --------------------- make the first hull closed contour ---------------------

# Number the grouped hull contours
hull_goup = []

# Create a copy of the input image to draw the hulls on
img_hull = np.zeros_like(image)

# Number the grouped contours
for i in range(len(grouped_contours)):
    # Calculate the centroid of the contour
    M = cv2.moments(grouped_contours[i])
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])

    # Convert the contour to a closed line
    hull = cv2.convexHull(grouped_contours[i])
    hull_goup.append(hull)
    cv2.drawContours(img_hull, [hull], 0, (0, 0, 255), 4)


# ------------------- make the hull connected to the border and fill the hull  ---------------------
# decide which to connect there is a threshold how many pixel the border can be away

# Draw the new convex hull on a black image
img_hull_border = np.zeros_like(image)

hull_goup_with_edge = []

# Iterate over all hulls in the hull group    
for hull in hull_goup:
    
    # Extract the edges from the convex hull
    # edge are always between two points
    # i dont know why but it works like that
    # [(x1,y2),(x2,y2)]
    edges = []
    for i in range(len(hull) - 1):
        edges.append((tuple(hull[i][0]), tuple(hull[i + 1][0])))
    edges.append((tuple(hull[-1][0]), tuple(hull[0][0])))


    # Define the threshold distance to the image border
    threshold = 20

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

    # Add the hull to the hull group
    hull_goup_with_edge.append(hull_from_edges)

    # Draw the hull on the image
    cv2.drawContours(img_hull_border, [hull_from_edges], 0, 255, -1)


# -------------------------- check if a Corner is close if yes fill all of the Corner ---------------------------
# Extract the edges from the convex hull
# edge are always between two points
# i dont know why but it works like that
# [(x1,y2),(x2,y2)]

# here we search for connections with the border
# if it is connected to 2 sides 
# then add a point at the corner
# [(0,0),(0,0)]

img_hull_corner = np.zeros_like(image)
new_group_all = []
for i, hull in enumerate(hull_goup_with_edge):

    # Extract the edges from the convex hull
    edges = []
    for i in range(len(hull) - 1):
        edges.append((tuple(hull[i][0]), tuple(hull[i + 1][0])))
    edges.append((tuple(hull[-1][0]), tuple(hull[0][0])))
    edges2 = edges.copy()
    for i, edge in enumerate(edges):
        print(edge)
        new_edge = []
        left, right, top, bottom = False, False, False, False
        for vertex in edge:
            print(vertex)
            x,y = vertex
            if x == 0:
                left = True
            if x == image.shape[1] - 1:
                right = True
            if y == 0:
                top = True 
            if y == image.shape[0] - 1:
                bottom = True
            if left and top and len(new_edge) <2:
                new_edge.append((0,0))
                new_edge.append((0,0))
            if left and bottom and len(new_edge) <2:
                new_edge.append((0,image.shape[0] - 1))
                new_edge.append((0,image.shape[0] - 1))
            if right and top and len(new_edge) <2:
                new_edge.append((image.shape[1] - 1,0))
                new_edge.append((image.shape[1] - 1,0))
            if right and bottom and len(new_edge) <2:
                new_edge.append((image.shape[1] - 1,image.shape[0] - 1))
                new_edge.append((image.shape[1] - 1,image.shape[0] - 1))
        if new_edge != []:
            edges2.append(tuple(new_edge))
    # Create a new convex hull from the updated edges
    hull_from_edges = cv2.convexHull(np.array(edges2).reshape(-1, 2), clockwise=False)
        # Add the hull to the hull group
    new_group_all.append(hull_from_edges)
    # Draw the hull on the image
    cv2.drawContours(img_hull_corner, [hull_from_edges], 0,(255,255,255), 2)


# -------------------------- make from the filled hullwith border and corner only the contour (finished_hull) ---------------------------

# Convert the image to grayscale
gray = cv2.cvtColor(img_hull_corner, cv2.COLOR_BGR2GRAY)
# Threshold the grayscale image to create a binary image
_, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

# Find contours in the binary image
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Create a copy of the input image to draw the hulls on
finished_hull = np.zeros_like(image)

# Draw the convex hulls around the contours
for contour in contours:
    hull = cv2.convexHull(contour)
    cv2.drawContours(finished_hull, [hull], 0, (0, 0, 255), 4)

# ------------------------------------------ make working zones ------------------------------------------



# ------------------------------------------ divide the hulls into the diffrent working zones ------------------------




# Show the original image, the edges, and the image with the new hull
cv2.imshow("Original Image", image)
cv2.imshow("img_contour", img_contour)
cv2.imshow("img_hull",img_hull)
cv2.imshow("img_hull_border", img_hull_border)
cv2.imshow("image_with_hull2", img_hull_corner)
cv2.imshow("finished_hull", finished_hull)
cv2.waitKey(0)
cv2.destroyAllWindows()



# Create an empty mask for the result
mask_only_hull_with_border = np.zeros_like(image)
