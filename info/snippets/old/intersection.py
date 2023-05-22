import cv2
import numpy as np
from sympy import Line, Point

def find_line_intersections(line_start, line_end, trapezoid):
    intersections = []
    line = Line(line_start, line_end)
    for side in trapezoid:
        pt1 = Point(side[0][0], side[0][1])
        pt2 = Point(side[1][0], side[1][1])
        side_line = Line(pt1, pt2)
        intersection = side_line.intersection(line)
        if intersection:
            intersection_point = intersection[0].evalf()
            x, y = intersection_point.x, intersection_point.y
            if min(pt1.x, pt2.x) <= x <= max(pt1.x, pt2.x) and min(pt1.y, pt2.y) <= y <= max(pt1.y, pt2.y):
                intersections.append((int(x), int(y)))
    return intersections




def make_parallel_line(point1, point2, distance):
    # Calculate the vector representing the given line
    vector = np.array(point2) - np.array(point1)

    # Calculate the perpendicular vector by swapping x and y components and changing the sign of one of them
    perpendicular_vector = np.array([-vector[1], vector[0]])

    # Normalize the perpendicular vector
    unit_perpendicular_vector = perpendicular_vector / np.linalg.norm(perpendicular_vector)

    # Calculate the offset vector based on the desired distance
    offset_vector = distance * unit_perpendicular_vector

    # Calculate the coordinates of the points on the parallel line
    parallel_point1 = tuple((np.array(point1) + offset_vector).astype(int))
    parallel_point2 = tuple((np.array(point2) + offset_vector).astype(int))

    return parallel_point1, parallel_point2

def extend_line(point1, point2, extension_percentage):
    # Calculate the vector representing the given line
    vector = np.array(point2) - np.array(point1)

    # Calculate the extension based on the line's length and the extension percentage
    extension = np.linalg.norm(vector) * extension_percentage

    # Calculate the extension vectors in the direction of the line
    extension_vector1 = (extension * vector) / np.linalg.norm(vector)
    extension_vector2 = -extension_vector1

    # Calculate the extended points
    extended_point1 = tuple((np.array(point1) + extension_vector1).astype(int))
    extended_point2 = tuple((np.array(point2) + extension_vector2).astype(int))

    return extended_point1, extended_point2

def find_extremum(points, axis='x'):
    # axis can be 'x' or 'y'
    # mode can be 'max' or 'min'
    
    if axis == 'x':
        idx = 0
    elif axis == 'y':
        idx = 1
    else:
        raise ValueError("Invalid axis value. Must be 'x' or 'y'.")
    
    extremum_point_max = max(points, key=lambda p: p[idx])
    extremum_point_min = min(points, key=lambda p: p[idx])

    return extremum_point_max, extremum_point_min


def interpolate_points(point1, point2, pixel_distance):
    # Calculate the vector between the two points
    vector = np.array(point2) - np.array(point1)

    # Calculate the actual distance between the two points
    actual_distance = np.linalg.norm(vector)

    # Calculate the scaling factor based on the desired pixel distance
    scale_factor = pixel_distance / actual_distance

    # Calculate the new point coordinates from the first point
    new_point1 = tuple((np.array(point1) + scale_factor * vector).astype(int))

    # Calculate the new point coordinates from the second point
    new_point2 = tuple((np.array(point2) - scale_factor * vector).astype(int))

    return new_point1, new_point2



# Define the trapezoid corner points
trapezoid = [
    [(150, 200), (350, 200)],
    [(100, 400),(400, 400)],
    [(100, 400),(150, 200)],
    [(400, 400),(350, 200)]
]

# Define the line start and end points
line_start = (0, 500)
line_end = (500, 0)

# How fare the parralel line should be from the original line
distance_a = 20

# How far the point should be for breaking and aceelerating
distance_b = 10

# How much the line should be extended
sizing_factor = 1.5

# Find the intersections
intersections = find_line_intersections(line_start, line_end, trapezoid)

middle_points = interpolate_points(intersections[0], intersections[1], distance_b)



# Next line 
new_points = make_parallel_line(intersections[0], intersections[1], distance_a)

new_points_long = extend_line(new_points[0], new_points[1], sizing_factor)

new_intersections = find_line_intersections(new_points_long[0], new_points_long[1], trapezoid)

new_middle_points = interpolate_points(new_intersections[0], new_intersections[1], distance_b)


# get maximum and minimum x and y values
x_max, x_min = find_extremum(trapezoid, axis='x')
y_max, y_min = find_extremum(trapezoid, axis='y')



# Draw the trapezoid, line, and intersections

img = np.zeros((500, 500, 3), dtype=np.uint8)

for side in trapezoid:
    cv2.line(img, (side[0][0], side[0][1]), (side[1][0], side[1][1]), (0, 0, 255), 1)

cv2.line(img, intersections[0], intersections[1], (0, 255, 0), 1)

for intersection in intersections:
    cv2.circle(img, intersection, 5, (0, 255, 255), -1)


for middle_point in middle_points:
    cv2.circle(img, middle_point, 5, (0, 255, 100), -1)



cv2.line(img, new_intersections[0], new_intersections[1], (0, 255, 0), 1)

for new_intersection in new_intersections:
    cv2.circle(img, new_intersection, 5, (0, 255, 255), -1)

for new_middle_point in new_middle_points:
    cv2.circle(img, new_middle_point, 5, (0, 255, 100), -1)



cv2.imshow("Trapezoid and Line", img)
cv2.waitKey(0)
cv2.destroyAllWindows()