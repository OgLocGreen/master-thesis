import cv2
import numpy as np

# Read in the image
img = cv2.imread('closed_contours.png')

# Convert the image to grayscale
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Threshold the image to create a binary image
ret, thresh = cv2.threshold(gray, 127, 255, 0)

# Find the contours in the binary image
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Select the largest contour (assuming it's the outer contour)
largest_contour = max(contours, key=cv2.contourArea)

# Convert the contour to a polygon
polygon = cv2.approxPolyDP(largest_contour, epsilon=0.01*cv2.arcLength(largest_contour, True), closed=True)

# Get the edges of the polygon
edges = []
for i in range(len(polygon)):
    edge = [[polygon[i][0][0], polygon[i][0][1]], [polygon[(i+1)%len(polygon)][0][0], polygon[(i+1)%len(polygon)][0][1]]]
    edges.append(edge)

# Print the edges as points and save them in an array
points = []
for edge in edges:
    p1 = tuple(edge[0])
    #p2 = tuple(edge[1])
    points.append(p1)
    #points.append(p2)
    cv2.circle(img, p1, 3, (0, 255, 0), 3)
    #cv2.circle(img, p2, 3, (0, 255, 0), 3)

# Draw the contour in yellow
#cv2.drawContours(img, [largest_contour], 0, (0, 255, 255), 3)

# Draw the polygon in red
#cv2.drawContours(img, [polygon], 0, (0, 0, 255), 2)

# Display the image with points
cv2.imshow('Image with points', img)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Save the edges in an array
edges_array = np.array(edges)

# Display the edges array
print('Edges array:')
print(edges_array)


"""
    array_hull_goup = []
    for hull in grouped_hulls_dilate:
        array_hull_points = []
        for point in hull:
            for x,y in point:
                array_hull_points.append([float(x),(y)])
        array_hull_goup.append(array_hull_points)



    image5 = np.copy(image)
    for point in array_hull_goup:
        # Convert the points to a NumPy array of shape (n,1,2)
        points_array = np.array([point], dtype=np.int32)
        # Draw the polygon on the image
        cv2.polylines(image5, [points_array], True, (0, 0, 255), thickness=2)
        """