import math
import cv2
import numpy as np

from sympy import Point, Line

def find_intersection(trapezoid_points, line_points):
    # Create points for the trapezoid
    A, B, C, D = trapezoid_points

    # Create points for the line
    P, Q = line_points

    # Create lines from the trapezoid points
    trap_line_1 = Line(A, B)
    trap_line_2 = Line(C, D)

    # Create a line from the given line points
    line = Line(P, Q)

    # Find the intersection points between the line and the trapezoid lines
    intersection_1 = trap_line_1.intersection(line)
    intersection_2 = trap_line_2.intersection(line)

    # Return the intersection points
    return intersection_1, intersection_2


def get_distance(p1, p2):
    return math.sqrt((p2[0] - p1[0])**2 + (p2[1] - p1[1])**2)

def get_parallel_line(p1, p2, distance):
    angle = math.atan2(p2[1] - p1[1], p2[0] - p1[0])
    dx = distance * math.sin(angle)
    dy = distance * math.cos(angle)
    return [(p1[0] + dx, p1[1] + dy), (p2[0] + dx, p2[1] + dy)]

# Get corner points of the trapezoid
point1 = (100, 100)
point2 = (400, 100)
point3 = (300, 300)
point4 = (200, 300)

# Define the distance from the inside line
distance = 45

# Create an image to draw the trapezoid and parallel lines
image = np.zeros((500, 500, 3), dtype=np.uint8)

# Draw the trapezoid
cv2.line(image, point1, point2, (255, 0, 0), 2)
cv2.line(image, point2, point3, (255, 0, 0), 2)
cv2.line(image, point3, point4, (255, 0, 0), 2)
cv2.line(image, point4, point1, (255, 0, 0), 2)

# Find the first line
line1 = (point1, point2)

# Calculate the length of the first line   #TODO: get max side length
line_length = get_distance(point1, point2) 

# Calculate the number of parallel lines that can fit inside the trapezoid
num_lines = int(line_length // distance)

# Create parallel lines inside the trapezoid
for i in range(1, num_lines + 1):
    current_distance = i * distance
    parallel_line = get_parallel_line(line1[0], line1[1], current_distance)
    
    # Clip the parallel line to ensure it stays within the trapezoid
    clipped_line = []
    for p in parallel_line:
        x = int(np.clip(p[0], min(point1[0], point4[0]), max(point2[0], point3[0])))
        y = int(np.clip(p[1], min(point1[1], point2[1]), max(point3[1], point4[1])))
        clipped_line.append((x, y))
    
    cv2.line(image, clipped_line[0], clipped_line[1], (0, 255, 0), 2)

# Display the image
cv2.imshow("Trapezoid with Parallel Lines", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
