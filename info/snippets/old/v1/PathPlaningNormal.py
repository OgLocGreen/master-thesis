import cv2
import numpy as np
import math

def draw_lines_diagonal(image, start_point, angle_degrees, line_color=(0, 0, 255), thickness=2):
    height, width, _ = image.shape

    # Convert the angle from degrees to radians
    angle_radians = math.radians(angle_degrees)

    # Calculate the line length based on the diagonal distance of the image
    diagonal_length = math.sqrt(width ** 2 + height ** 2)
    line_length = diagonal_length
    # Calculate the end point of the line
    end_point_x = int(start_point[0] + line_length * math.cos(angle_radians))
    end_point_y = int(start_point[1] + line_length * math.sin(angle_radians))

    # Ensure the end point is within the image boundaries
    end_point_x = max(0, min(end_point_x, width - 1))
    end_point_y = max(0, min(end_point_y, height - 1))
    end_point = (end_point_x, end_point_y)

    # Draw the line on the image
    cv2.line(image, start_point, end_point, line_color, thickness=thickness)

    return image


def draw_lines_intersection(image, start_point, angle_degrees, line_color=(0, 0, 255), thickness=2):
    height, width, _ = image.shape

    # Convert the angle from degrees to radians
    angle_radians = math.radians(angle_degrees)

    # Calculate the slope of the line
    slope = math.tan(angle_radians)

    # Calculate the intersection points with the image boundaries
    x0 = 0
    y0 = int(start_point[1] - (start_point[0] - x0) * slope)
    if y0 < 0 or y0 >= height:
        y0 = 0
        x0 = int(start_point[0] - (start_point[1] - y0) / slope)

    x1 = width - 1
    y1 = int(start_point[1] + (x1 - start_point[0]) * slope)
    if y1 < 0 or y1 >= height:
        y1 = height - 1
        x1 = int(start_point[0] + (y1 - start_point[1]) / slope)

    # Calculate the end points of the line
    end_point1 = (x0, y0)
    end_point2 = (x1, y1)

    # Draw the lines on the image
    cv2.line(image, start_point, end_point1, line_color, thickness=thickness)
    cv2.line(image, start_point, end_point2, line_color, thickness=thickness)

    return image


# Example usage:
image = np.zeros((500, 500, 3), dtype=np.uint8)
start_point = (250, 250)
angle_degrees = 45
result_image_diagonal = draw_lines_diagonal(image, start_point, angle_degrees)

result_image_intersection = draw_lines_intersection(image, start_point, angle_degrees)

cv2.imshow("Result diagonal", result_image_diagonal)
cv2.waitKey(0)

cv2.imshow("Result sides", result_image_intersection)
cv2.waitKey(0)