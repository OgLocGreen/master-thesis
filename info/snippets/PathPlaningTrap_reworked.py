import cv2
import numpy as np
from sympy import Line, Point, Line2D
import matplotlib.pyplot as plt

def get_corner(points):
    """
    Get the corner points of a trapezoid.

    Args:
        points (list): List of four points representing a trapezoid.

    Returns:
        tuple: Tuple of four corner points (top_left, top_right, bottom_left, bottom_right).
    """
    # Ensure that we have exactly four points
    if len(points) != 4:
        raise ValueError("Trapezoid should have exactly four points.")

    points = [[int(x), int(y)] for x, y in points]
    # Sort the points based on their y-coordinates
    sorted_points = sorted(points, key=lambda p: p[1])

    # Determine the top points and bottom points
    top_points = sorted(sorted_points[:2], key=lambda p: p[0])
    bottom_points = sorted(sorted_points[2:], key=lambda p: p[0])

    # Return the corner points
    top_left = top_points[0]
    top_right = top_points[1]
    bottom_left = bottom_points[0]
    bottom_right = bottom_points[1]

    return top_left, top_right, bottom_left, bottom_right


def find_line_intersections(line_start, line_end, trapezoid):
    """
    Find the intersections between a line and a trapezoid.

    Args:
        line_start (tuple): Start point of the line.
        line_end (tuple): End point of the line.
        trapezoid (list): List of four points representing a trapezoid.

    Returns:
        list: List of intersection points.
    """
    intersections = []

    line = Line(line_start, line_end)
    for side in trapezoid:
        pt1 = Point(side[0][0], side[0][1])
        pt2 = Point(side[1][0], side[1][1])
        side_line = Line(pt1, pt2)
        intersection = side_line.intersection(line)
        if intersection == [] or isinstance(intersection[0], Line2D):
            pass
        else:
            try:
                intersection_point = intersection[0].evalf()
                x, y = intersection_point.x, intersection_point.y
                if min(pt1.x, pt2.x) <= x <= max(pt1.x, pt2.x) and min(pt1.y, pt2.y) <= y <= max(pt1.y, pt2.y):
                    intersections.append((int(x), int(y)))
            except IndexError:
                pass
    return intersections


def make_parallel_line(point1, point2, distance, direction):
    """
    Make a parallel line to the given line.

    Args:
        point1 (tuple): First point on the line.
        point2 (tuple): Second point on the line.
        distance (float): Distance between the original line and the parallel line.
        direction (str): Direction of the line (e.g., "left-right", "up-down", "right-left", "down-up").

    Returns:
        tuple: Two points on the parallel line.
    """
    # Calculate the vector representing the given line
    vector = np.array(point2) - np.array(point1)

    # Calculate the perpendicular vector by swapping x and y components and changing the sign of one of them
    perpendicular_vector = np.array([-vector[1], vector[0]])

    # Normalize the perpendicular vector
    unit_perpendicular_vector = perpendicular_vector / np.linalg.norm(perpendicular_vector)

    # Calculate the offset vector based on the desired distance
    offset_vector = distance * unit_perpendicular_vector
    offset_vector = np.abs(offset_vector)

    # Calculate the coordinates of the points on the parallel line
    if direction == "left-right":
        offset_vector = offset_vector
    elif direction == "up-down":
        offset_vector = -offset_vector
    elif direction == "right-left":
        offset_vector = -offset_vector
    elif direction == "down-up":
        offset_vector = offset_vector

    parallel_point1 = tuple((np.array(point1) + offset_vector).astype(int))
    parallel_point2 = tuple((np.array(point2) + offset_vector).astype(int))

    return parallel_point1, parallel_point2


def extend_line(point1, point2, extension_percentage):
    """
    Extend a line by a given percentage.

    Args:
        point1 (tuple): First point on the line.
        point2 (tuple): Second point on the line.
        extension_percentage (float): Percentage by which to extend the line.

    Returns:
        tuple: Two points on the extended line.
    """
    # Calculate the vector representing the given line
    vector = np.array(point2) - np.array(point1)

    # Calculate the extension based on the line's length and the extension percentage
    extension = np.linalg.norm(vector) * extension_percentage

    # Calculate the extension vectors in the direction of the line
    extension_vector1 = (extension * vector) / np.linalg.norm(vector)
    extension_vector2 = -extension_vector1

    # Calculate the extended points
    extended_point1 = tuple((np.array(point1) + extension_vector2).astype(int))
    extended_point2 = tuple((np.array(point2) + extension_vector1).astype(int))

    return extended_point1, extended_point2


def interpolate_points(point1, point2, pixel_distance):
    """
    Interpolate points between two given points at a specific pixel distance.

    Args:
        point1 (tuple): First point.
        point2 (tuple): Second point.
        pixel_distance (int): Desired pixel distance between the interpolated points.

    Returns:
        tuple: Two interpolated points.
    """
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


def change_order(array):
    """
    Change the order of points in an array.

    Args:
        array (list): List of points.

    Returns:
        list: Updated list with changed point order.
    """
    for i in range(len(array)):
        if i % 2 == 1:
            start = array[i][-1]
            end = array[i][0]
            array[i][0] = start
            array[i][-1] = end
    return array


def generate_trapezoid_path(trapezoid, distance_a, distance_b, sizing_factor, direction):
    """
    Generate a path within a trapezoid.

    Args:
        trapezoid (list): List of four points representing a trapezoid.
        distance_a (float): Distance between the original line and the parallel line.
        distance_b (float): Distance between the intersection points and the middle points.
        sizing_factor (float): Factor by which to extend the lines.
        direction (str): Direction of the robot's movement.

    Returns:
        list: List of points representing the generated path.
    """
    top_left_point, top_right_point, bottom_left_point, bottom_right_point = get_corner(trapezoid)

    trapezoid = [[top_left_point, top_right_point],
                 [bottom_left_point, bottom_right_point],
                 [bottom_left_point, top_left_point],
                 [bottom_right_point, top_right_point]]

    # Define the line start and end points
    if direction == "left-right":
        line_start = top_left_point
        line_end = bottom_left_point
    elif direction == "down-up":
        line_start = top_left_point
        line_end = top_right_point
    elif direction == "right-left":
        line_start = top_right_point
        line_end = bottom_right_point
    elif direction == "up-down":
        line_start = bottom_left_point
        line_end = bottom_right_point

    # Array of Points for the path
    path_points = []
    path_points_with_direction_speed = []

    # Make the first line parallel to the original line
    start_point_parallel, end_point_parallel = make_parallel_line(line_start, line_end, distance_a, direction)
    start_point_extended, end_point_extended = extend_line(start_point_parallel, end_point_parallel, sizing_factor)

    intersections = find_line_intersections(start_point_extended, end_point_extended, trapezoid)
    if intersections == []:
        raise ValueError("No Path could be Calculated, check parameters")
    middle_points = interpolate_points(intersections[0], intersections[1], distance_b)
    path_points.append([intersections[0], middle_points[0], middle_points[1], intersections[1]])

    while True:
        new_points = make_parallel_line(intersections[0], intersections[1], distance_a, direction)
        new_points_long = extend_line(new_points[0], new_points[1], sizing_factor)

        new_intersections = find_line_intersections(new_points_long[0], new_points_long[1], trapezoid)

        # Check if the intersection are two different points or there are no intersections
        if new_intersections == [] or (new_intersections[0] == new_intersections[1] and len(new_intersections) == 2):
            break
        else:  # If there are more than one intersection point, check if the other is usable
            if new_intersections[0] == new_intersections[1] and new_intersections[0] != new_intersections[2]:
                new_intersections[1] = new_intersections[2]
            elif len(new_intersections) > 2 and new_intersections[0] != new_intersections[2]:
                break

            new_middle_points = interpolate_points(new_intersections[0], new_intersections[1], distance_b)

            path_points.append([new_intersections[0], new_middle_points[0], new_middle_points[1], new_intersections[1]])

            path_points_with_direction_speed.append(path_points[-1][0])

            intersections[0], intersections[1] = new_intersections[0], new_intersections[1]

    path_points = change_order(path_points)

    return path_points


if __name__ == '__main__':
    # Define the trapezoid
    trapezoid = [[150, 150], [350, 200], [100, 500], [400, 400]]

    # Define the parameters
    distance_a = 5
    distance_b = 5
    sizing_factor = 0.8
    direction = "right-left"

    # Draw the trapezoid, line, and intersections
    img = np.zeros((500, 500, 3), dtype=np.uint8)
    img2 = np.zeros((500, 500, 3), dtype=np.uint8)

    top_left_point, top_right_point, bottom_left_point, bottom_right_point = get_corner(trapezoid)

    trapezoid2 = [[top_left_point, top_right_point],
                  [bottom_left_point, bottom_right_point],
                  [bottom_left_point, top_left_point],
                  [bottom_right_point, top_right_point]]

    for side in trapezoid2:
        cv2.line(img, (int(side[0][0]), int(side[0][1])), (int(side[1][0]), int(side[1][1])), (0, 0, 255), 1)

    path_points = generate_trapezoid_path(trapezoid, distance_a, distance_b, sizing_factor, direction)

    for i, points in enumerate(path_points):
        if i % 2 == 0:
            cv2.line(img, points[0], points[-1], (0, 255, 0), 1)
        else:
            cv2.line(img, points[0], points[-1], (255, 255, 0), 1)
        cv2.circle(img, points[0], 5, (255, 255, 0), -1)
        cv2.circle(img, points[1], 5, (0, 255, 100), -1)
        cv2.circle(img, points[2], 5, (0, 255, 100), -1)
        cv2.circle(img, points[-1], 5, (255, 255, 0), -1)

    cv2.imshow("Trapezoid and Line", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()





    generate_line_picture(45)
    print("done")
