import cv2
import numpy as np
from sympy import Line, Point
import math


def find_line_intersections(line_start, line_end, trapezoid):
    intersections = []
    line = Line(line_start, line_end)
    for side in trapezoid:
        pt1 = Point(side[0][0], side[0][1])
        pt2 = Point(side[1][0], side[1][1])
        side_line = Line(pt1, pt2)
        intersection = side_line.intersection(line)
        try:
            intersection_point = intersection[0].evalf()
            x, y = intersection_point.x, intersection_point.y
            if min(pt1.x, pt2.x) <= x <= max(pt1.x, pt2.x) and min(pt1.y, pt2.y) <= y <= max(pt1.y, pt2.y):
                intersections.append((int(x), int(y)))
        except IndexError:
            pass
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
    offset_vector = np.abs(offset_vector)

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

def find_maximum_distance(points, axis):
    # Convert the points list to a NumPy array
    points_array = np.array(points)

    # Extract the x-coordinates and y-coordinates from the array
    x_coords = points_array[:, :, 0]
    y_coords = points_array[:, :, 1]

    # Calculate the maximum distance in the x-direction
    if axis == 'x':
        max_distance = np.max(np.abs(np.ptp(x_coords, axis=1)))

    # Calculate the maximum distance in the y-direction
    elif axis == 'y':
        max_distance = np.max(np.abs(np.ptp(y_coords, axis=1)))

    else:
        raise ValueError("Invalid axis argument. Please use 'x' or 'y'.")

    return max_distance



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

def change_order(array):
    for i in range(len(array)):
        if i % 2 == 1:
            start = array[i][-1]
            end = array[i][0]
            array[i][0] = start
            array[i][-1] = end
    return array


def generate_trapezoid_path(trapezoid, distance_a, distance_b, sizing_factor):

    # Speed for each point
    # 0 speeds inbetween middle points
    # 1 speeds at the middle points

    # Orientiation for each point

    # [ [x,y],[orientiation(pose), speed, direction_speed]]
    # [ [x=100,y],[orientiation(pose), speed, direction_speed]]



    # Working zones
    # Convex zones -> always because its easier


    # Matlab code
    # if Plate rectangular -> 4 workingzones
    # if Plate diffrent wie have more workingzones
    # 


    trapezoid = [[trapezoid[0], trapezoid[1]],
                    [trapezoid[2], trapezoid[3]],
                    [trapezoid[2], trapezoid[0]],
                    [trapezoid[3], trapezoid[1]]]

    # Define the line start and end points
    line_start = trapezoid[0][0]
    line_end = trapezoid[0][1]

    # get maximum and minimum x and y values
    x_max = find_maximum_distance(trapezoid, axis='x')
    y_max = find_maximum_distance(trapezoid, axis='y')


    # Number of lines needed to cover the trapezoid 
    number_of_lines = int(math.ceil(y_max / distance_a))+3    #TODO: find out which is the correct number of lines
                                                                    # also how to claculate the number of lines needed

    #if number_of_lines % 2 == 0:
    #    number_of_lines -= 2
    #else:
    #    number_of_lines -= 1

    # Array of Points for the path
    path_points = []

    # Make the first line parallel to the original line
    start_point, end_point = make_parallel_line(line_start, line_end, distance_a)
    start_point, end_point = extend_line(start_point, end_point, sizing_factor)

    intersections = find_line_intersections(start_point, end_point, trapezoid)
    middle_points = interpolate_points(intersections[0], intersections[1], distance_b)
    path_points.append([intersections[0], middle_points[0], middle_points[1], intersections[1]])

    # Draw the first line and intersections
    for _ in range(number_of_lines):
        new_points = make_parallel_line(intersections[0], intersections[1], distance_a)
        new_points_long = extend_line(new_points[0], new_points[1], sizing_factor)
        new_intersections = find_line_intersections(new_points_long[0], new_points_long[1], trapezoid)
        new_middle_points = interpolate_points(new_intersections[0], new_intersections[1], distance_b)


        path_points.append([new_intersections[0], new_middle_points[0], new_middle_points[1], new_intersections[1]])
        intersections[0], intersections[1] = new_intersections[0], new_intersections[1]

    path_points = change_order(path_points)

    return path_points

if __name__ == '__main__':

    # Define the trapezoid the sides
    trapezoid = [
        [[150, 200], [350, 200]],
        [[100, 400], [400, 400]],
        [[100, 400], [150, 200]],
        [[400, 400], [350, 200]]
    ]

    trapezoid = [
        [150, 150], [350, 200],[100, 500], [400, 400]
    ]


    #TODO: Test this it is not finished missing some lines at the end


    # How fare the parralel line should be from the original line
    distance_a = 15

    # How far the point should be for breaking and aceelerating
    distance_b = 10

    # How much the line should be extended
    sizing_factor = 1.5

    # Draw the trapezoid, line, and intersections
    img = np.zeros((500, 500, 3), dtype=np.uint8)

    path_points2 = generate_trapezoid_path(trapezoid, distance_a, distance_b, sizing_factor)

    trapezoid = [[trapezoid[0], trapezoid[1]],
                    [trapezoid[2], trapezoid[3]],
                     [trapezoid[2], trapezoid[0]],
                    [trapezoid[3], trapezoid[1]]]

    for side in trapezoid:
        cv2.line(img, (side[0][0], side[0][1]), (side[1][0], side[1][1]), (0, 0, 255), 1)

    for i,points in enumerate(path_points2):
        if i & 1 == 0:
            cv2.line(img, points[0], points[-1], (0, 255, 0), 1)
        else:
            cv2.line(img, points[0], points[-1], (255, 255, 0), 1)
        cv2.circle(img, points[0], 5, (255, 255, 0), -1)
        cv2.circle(img, points[1], 5, (0, 255, 100), -1)
        cv2.circle(img, points[2], 5, (0, 255, 100), -1)
        cv2.circle(img, points[-1], 5, (255, 255, 0), -1)


    # Add 



    cv2.imshow("Trapezoid and Line", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

