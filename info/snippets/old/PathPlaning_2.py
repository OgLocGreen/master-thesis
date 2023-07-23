import cv2
import numpy as np
from sympy import Line, Point, Line2D

def find_line_intersections(line_start, line_end, polygon):
    """
    Find the intersections between a line and a points.

    Args:
        line_start (tuple): Start point of the line.
        line_end (tuple): End point of the line.
        polygon (list): List of points representing a polygon.

    Returns:
        list: List of intersection points.
    """
    intersections = []

    line = Line(line_start, line_end)

    point_old = None
    for points in polygon:
        if point_old == None:
            point_old = points
        else:
            point_new = points
            line2 = Line(point_old, point_new)
            intersection = line.intersection(line2)
            if intersection == [] or isinstance(intersection[0], Line2D):
                pass
            else:
                try:
                    intersection_point = intersection[0].evalf()
                    x, y = intersection_point.x, intersection_point.y
                    if min(point_old[0], point_new[0]) <= x <= max(point_old[0], point_new[0]) and min(point_old[1], point_new[1]) <= y <= max(point_old[1], point_new[1]):
                        intersections.append((int(x), int(y)))
                except IndexError:
                    pass
            point_old = point_new
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
    if direction == 1:
        offset_vector = offset_vector
    elif direction == -1:
        offset_vector = -offset_vector

    parallel_point1 = tuple((np.array(point1) + offset_vector).astype(int))
    parallel_point2 = tuple((np.array(point2) + offset_vector).astype(int))

    return parallel_point1, parallel_point2


def intersection(line1, line2):
    """Returns the point of intersection of two lines."""
    xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0])
    ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1])

    def det(a, b):
        return a[0] * b[1] - a[1] * b[0]

    div = det(xdiff, ydiff)
    if div == 0:
       return None

    d = (det(*line1), det(*line2))
    x = det(d, xdiff) / div
    y = det(d, ydiff) / div
    return int(x), int(y)


def draw_line(img, start_point, angle, color=(255, 255, 255), thickness=1):
    # Convert the angle to radians
    angle_rad = np.deg2rad(angle)

    # Calculate the direction of the line
    dir_x = np.cos(angle_rad)
    dir_y = np.sin(angle_rad)

    # Calculate the opposite direction
    opp_dir_x = -dir_x
    opp_dir_y = -dir_y

    # Find the height and width of the image
    height, width = img.shape[:2]

    # Calculate the max distance from the start point to a corner of the image
    max_dist = np.hypot(height, width)

    # Calculate the end points
    end_point_1 = (int(start_point[0] + dir_x * max_dist), int(start_point[1] + dir_y * max_dist))
    end_point_2 = (int(start_point[0] + opp_dir_x * max_dist), int(start_point[1] + opp_dir_y * max_dist))

    # Draw the lines
    img = cv2.line(img, start_point, end_point_1, color, thickness)
    img = cv2.line(img, start_point, end_point_2, color, thickness)
    
    line = [end_point_1, end_point_2]

    return img, line

def draw_line_old(img, start_point, angle, color=(255, 255, 255), thickness=1):
    line = []
    # Find the height and width of the image
    height, width = img.shape[:2]

    # Convert the angle to radians
    angle_rad = np.deg2rad(angle)

    # Define the image boundary lines
    boundaries = [
        [(0, 0), (width, 0)],  # top
        [(width, 0), (width, height)],  # right
        [(width, height), (0, height)],  # bottom
        [(0, height), (0, 0)]  # left
    ]

    for direction in [-1, 1]:
        # Calculate end point in the given direction
        end_point_x = start_point[0] + direction * np.cos(angle_rad) * max(width, height) * 2
        end_point_y = start_point[1] + direction * np.sin(angle_rad) * max(width, height) * 2
        end_point = (end_point_x, end_point_y)

        # Find the intersection of the line with each boundary
        intersections = [intersection((start_point, end_point), boundary) for boundary in boundaries]

        # Filter out None values and out-of-bounds intersections
        intersections = [(x, y) for (x, y) in intersections 
                        if x is not None and y is not None and 0 <= x < width and 0 <= y < height]

        if intersections:
            # Use the intersection that gives the longest line
            end_point = max(intersections, key=lambda p: np.hypot(p[0]-start_point[0], p[1]-start_point[1]))

            # Draw the line on the image
            img = cv2.line(img, start_point, end_point, color, thickness)
            line.append(end_point)
    return img, line

def compute_center_of_mass(points):
    x_coords = [p[0] for p in points]
    y_coords = [p[1] for p in points]
    centroid_x = int(sum(x_coords) / len(points))
    centroid_y = int(sum(y_coords) / len(points))
    return (centroid_x, centroid_y)


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


def calculate_path(img, polygon, angle, distance_a, distance_b, direction, sizing_factor):
    """
    Calculate the optimal path on a given polygon using a starting angle.

    Parameters:
    img (np.array): The input image on which to draw the polygon and the path.
    polygon (list): List of points representing the polygon.
    angle (float): The initial angle for the starting line.
    distance_a (int): The distance between the two lines.
    distance_b (int): The distance between the two points on the line.
    direction (int): Direction for making parallel lines (-1 or 1).
    sizing_factor (float): Scaling factor for line extension.

    Returns:
    path_points (list): A list of points representing the calculated path.
    """

    # Draw the trapezoid
    polygon.append(polygon[0])
    old_point = []
    for point in polygon:
        if old_point == []:
            old_point = point
        else:
            cv2.line(img, (old_point[0], old_point[1]), (point[0], point[1]), (0, 0, 255), 1)
            old_point = point

    # Calculate Center of Mass as Starting Point
    start_point = compute_center_of_mass(polygon)
    img, line = draw_line(img, start_point, angle)

    # Find the intersection of the line with the Polygon
    point_1, point_2 = line[0], line[1]

    while True:
        # Shift the line until it doesn't intersect the Polygon
        point_1, point_2 = make_parallel_line(point_1, point_2, 10 ,1)
        # Check if the line intersects the trapezoid
        intersection = find_line_intersections(point_1, point_2, polygon)

        if intersection != []:
            pass
        else:
            break
        
        cv2.line(img, point_1, point_2, (0, 255, 0), 1)
        cv2.imshow("Trapezoid and Line", img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()


    # Make the Path Array
    path_points = []

    # Make the first line parallel to the original line
    start_point_parallel, end_point_parallel = make_parallel_line(point_1, point_2, distance_a, direction)
   # start_point_extended, end_point_extended = extend_line(start_point_parallel, end_point_parallel, sizing_factor)

    intersections = find_line_intersections(start_point_parallel, end_point_parallel, polygon)
    if intersections == []:
        raise ValueError("No Path could be Calculated, check parameters")
    middle_points = interpolate_points(intersections[0], intersections[1], distance_b)
    path_points.append([intersections[0], middle_points[0], middle_points[1], intersections[1]])

    while True:
        new_points = make_parallel_line(intersections[0], intersections[1], distance_a, direction)
        #new_points_long = extend_line(new_points[0], new_points[1], sizing_factor)
        new_intersections = find_line_intersections(new_points[0], new_points[1], polygon)
        if new_intersections == [] or (new_intersections[0] == new_intersections[1] and len(new_intersections) == 2):
            break
        else:  # If there are more than one intersection point, check if the other is usable
            if new_intersections[0] == new_intersections[1] and new_intersections[0] != new_intersections[2]:
                new_intersections[1] = new_intersections[2]
            elif len(new_intersections) > 2 and new_intersections[0] != new_intersections[2]:
                break
        
            new_middle_points = interpolate_points(new_intersections[0], new_intersections[1], distance_b)

            path_points.append([new_intersections[0], new_middle_points[0], new_middle_points[1], new_intersections[1]])

            intersections[0], intersections[1] = new_intersections[0], new_intersections[1]
    path_points = change_order(path_points)
    return path_points


if __name__ == '__main__':

    # Draw the trapezoid, line, and intersections
    img = np.zeros((500, 500, 3), dtype=np.uint8)

    # Define the trapezoid
    polygon = [[100, 150], [100, 450], [200, 420], [400, 400] ,[350, 200]]

    # Draw the trapezoid
    polygon.append(polygon[0])
    old_point = []
    for point in polygon:
        if old_point == []:
            old_point = point
        else:
            cv2.line(img, (old_point[0], old_point[1]), (point[0], point[1]), (0, 0, 255), 1)
            old_point = point


    polygon = [[100, 150], [100, 450], [200, 420], [400, 400] ,[350, 200]]

    #Make the Path Array
    distance_a = 20 # between the two lines
    distance_b = 25 # between the two points
    direction = -1
    sizing_factor = 0.6
    angle = 45
    path_points = []

    # Make the first line parallel to the original line
    path_points = calculate_path(img, polygon, angle, distance_a, distance_b, direction, sizing_factor)

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