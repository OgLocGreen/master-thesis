import cv2
import numpy as np
from sympy import Line, Point
import math

def find_corners(polygon):
    #    topmost,leftmost ───────────►xxxxxxxxxx◄────────── topmost,rightmost
    #                              xxxx         xx
    #    leftmost,topmost ──────►xxx             xx
    #                            x                xx◄────── rightmost,topmost
    #                            x                 x
    # leftmost,bottommost ──────►xx                x
    #                             xx              xx◄────── rightmost,bottommost
    #                              x             xx
    # bottommost,leftmost ────────►xxxxxxxxxxxxxxx◄──────── bottommost,rightmost

    # topmost is minimum Y
    # leftmost is minimum X
    # rightmost is maximum X, or minimum -X
    # bottommost is maximum Y, or minimum -Y
    # X is `pt[0][0]`, Y is `pt[0][1]`

    # going clock-wise :
    topmost_then_rightmost_point =    min(polygon, key=lambda pt: ( pt[1], -pt[0]))
    rightmost_then_topmost_point =    min(polygon, key=lambda pt: (-pt[0],  pt[1]))
    rightmost_then_bottommost_point = min(polygon, key=lambda pt: (-pt[0], -pt[1]))
    bottommost_then_rightmost_point = min(polygon, key=lambda pt: (-pt[1], -pt[0]))
    bottommost_then_leftmost_point =  min(polygon, key=lambda pt: (-pt[1],  pt[0]))
    leftmost_then_bottommost_point =  min(polygon, key=lambda pt: ( pt[0], -pt[1]))
    leftmost_then_topmost_point =     min(polygon, key=lambda pt: ( pt[0],  pt[1]))
    topmost_then_leftmost_point =     min(polygon, key=lambda pt: ( pt[1],  pt[0]))

    top_left = leftmost_then_topmost_point
    top_right = rightmost_then_topmost_point
    bottom_right = leftmost_then_bottommost_point
    bottom_left = rightmost_then_bottommost_point

    #return tuple(top_left), tuple(top_right), tuple(bottom_right), tuple(bottom_left)
    return top_left, top_right, bottom_right, bottom_left

def get_corner(points):
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
    intersections = []

    line = Line(line_start, line_end)
    for side in trapezoid:
        pt1 = Point(side[0][0], side[0][1])
        pt2 = Point(side[1][0], side[1][1])
        side_line = Line(pt1, pt2)
        intersection = side_line.intersection(line)
        if intersection == []:
            pass
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

    # Calculate the extended points   #TODO: Why is the Start Point now more left then the end point?
    extended_point1 = tuple((np.array(point1) + extension_vector2).astype(int))
    extended_point2 = tuple((np.array(point2) + extension_vector1).astype(int))

    return extended_point1, extended_point2

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
    top_left_point, top_right_point, bottom_left_point, bottom_right_point = get_corner(trapezoid)

    trapezoid = [[top_left_point, top_right_point],
                    [bottom_left_point, bottom_right_point],
                    [bottom_left_point, top_left_point],
                    [bottom_right_point, top_right_point]]


    # Define the line start and end points
    # TODO: Intetegieren von einer funktion die mir die richtung vorgibt welche seite als erstes benutzt werden soll.
    line_start = top_left_point
    line_end = bottom_left_point

    

    # Array of Points for the path
    path_points = []

    # Make the first line parallel to the original line

    start_point, end_point = make_parallel_line(line_start, line_end, distance_a)
    start_point, end_point = extend_line(start_point, end_point, sizing_factor)







    points = top_left_point, top_right_point, bottom_left_point, bottom_right_point
    img2 = np.zeros((500, 500, 3), dtype=np.uint8)


        # Ensure that we have exactly four points
    if len(points) != 4:
        raise ValueError("Trapezoid should have exactly four points.")

    points = [[int(x), int(y)] for x, y in points]
    # Sort the points based on their y-coordinates
    sorted_points = sorted(points, key=lambda p: p[1])

    # Determine the top points and bottom points
    top_points = sorted(sorted_points[:2], key=lambda p: p[0])
    bottom_points = sorted(sorted_points[2:], key=lambda p: p[0])
    color=(0, 255, 0)
    thickness=1
    # Draw the trapezoid edges
    cv2.line(img2, tuple(top_points[0]), tuple(top_points[1]), color, thickness)
    cv2.line(img2, tuple(top_points[1]), tuple(bottom_points[1]), color, thickness)
    cv2.line(img2, tuple(bottom_points[1]), tuple(bottom_points[0]), color, thickness)
    cv2.line(img2, tuple(bottom_points[0]), tuple(top_points[0]), color, thickness)

    # Return the corner points

    cv2.line(img2, start_point, end_point, (0, 255, 255), thickness)


    cv2.imshow("Trapezoid and Line", img2)
    cv2.waitKey(0)
    cv2.destroyAllWindows()






    intersections = find_line_intersections(start_point, end_point, trapezoid)
    middle_points = interpolate_points(intersections[0], intersections[1], distance_b)
    path_points.append([intersections[0], middle_points[0], middle_points[1], intersections[1]])

    while True:
        new_points = make_parallel_line(intersections[0], intersections[1], distance_a)
        new_points_long = extend_line(new_points[0], new_points[1], sizing_factor)
        new_intersections = find_line_intersections(new_points_long[0], new_points_long[1], trapezoid)
        if new_intersections == [] or new_intersections[0] == new_intersections[1]:
            break
        else:
            new_middle_points = interpolate_points(new_intersections[0], new_intersections[1], distance_b)
            path_points.append([new_intersections[0], new_middle_points[0], new_middle_points[1], new_intersections[1]])
            intersections[0], intersections[1] = new_intersections[0], new_intersections[1]

    path_points = change_order(path_points)

    return path_points

if __name__ == '__main__':

    # Define the trapezoid the sides
    # trapezoid = [top_left_point, top_right_point, bottom_left_point, bottom_right_point]

    #trapezoid = [[100, 100], [200, 100],[100, 200], [200, 200]]

    #trapezoid = [[150, 150], [350, 200],[100, 500], [400, 400]]

    #trapezoid = [[339.479, 479.0], [339.479, 338.6995025896108], [345.339, 339.0], [345.339, 476.25573672783]]
    trapezoid = [[100, 100],[250, 100], [190, 150], [200, 200]]
    trapezoid = [[179.468, 468.0], [179.468, 335.2288123481492], [189.331, 331.0], [189.331, 472.0052166307438]]

    #TODO: if the angle is to small btw. the area is to small to have the speed up what should we do?
    # just let this line out? or should he run it with a lower speed?
    # for now the points are wrong and will be out side of the trapezoid 



    # TODO: Why Trepezoid and not just a polygone?
    # with the Workinzone i know whiche direction the robot goes
    # so i can just get the most left point and then start making lines from there
    # and get the intersections with the polygone
    # because the trapzoids are realy small and the speeding up and breaking would make sometimes no sense
    # and problems couse it would be to small


    # How fare the parralel line should be from the original line
    distance_a = 2

    # How far the point should be for breaking and aceelerating
    distance_b = 10

    # How much the line should be extended
    sizing_factor = 0.25

    # Draw the trapezoid, line, and intersections
    img = np.zeros((500, 500, 3), dtype=np.uint8)
    img2 = np.zeros((500, 500, 3), dtype=np.uint8)
    img3 = np.zeros((500, 500, 3), dtype=np.uint8)


    top_left_point, top_right_point, bottom_left_point, bottom_right_point = get_corner(trapezoid)

    trapezoid2 = [[top_left_point, top_right_point],
                    [bottom_left_point, bottom_right_point],
                    [bottom_left_point, top_left_point],
                    [bottom_right_point, top_right_point]]
    


    for side in trapezoid2:
        cv2.line(img, (int(side[0][0]), int(side[0][1])), (int(side[1][0]), int(side[1][1])), (0, 0, 255), 1)



    path_points = generate_trapezoid_path(trapezoid, distance_a, distance_b, sizing_factor)


    for i,points in enumerate(path_points):
        if i & 1 == 0:
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