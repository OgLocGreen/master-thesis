import cv2
import numpy as np

def are_lines_parallel(line1_point1, line1_point2, line2_point1, line2_point2):
    # Calculate the slopes of the lines
    slope1 = (line1_point2[1] - line1_point1[1]) / (line1_point2[0] - line1_point1[0])
    slope2 = (line2_point2[1] - line2_point1[1]) / (line2_point2[0] - line2_point1[0])

    # Compare the slopes to check if the lines are parallel
    return slope1 == slope2

def are_lines_parallel2(line1_point1, line1_point2, line2_point1, line2_point2):
    # Calculate the gradients of the lines
    gradient1 = float("inf") if line1_point2[0] == line1_point1[0] else (line1_point2[1] - line1_point1[1]) / (line1_point2[0] - line1_point1[0])
    gradient2 = float("inf") if line2_point2[0] == line2_point1[0] else (line2_point2[1] - line2_point1[1]) / (line2_point2[0] - line2_point1[0])

    # Compare the gradients to check if the lines are parallel
    return gradient1 == gradient2

def draw_parallel_line(point1, point2, distance):
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

def make_parallel_extend_line(point1, point2, distance, extension_percentage):
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


        # Calculate the vector representing the given line
    vector = np.array(parallel_point2) - np.array(parallel_point1)

    # Calculate the extension based on the line's length and the extension percentage
    extension = np.linalg.norm(vector) * extension_percentage

    # Calculate the extension vectors in the direction of the line
    extension_vector1 = (extension * vector) / np.linalg.norm(vector)
    extension_vector2 = -extension_vector1

    # Calculate the extended points
    extended_point1 = tuple((np.array(point1) + extension_vector1).astype(int))
    extended_point2 = tuple((np.array(point2) + extension_vector2).astype(int))

    return extended_point1, extended_point2


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



# Example usage
point1 = (50, 100)  # (x, y) coordinates of the first point on the original line
point2 = (350, 300)  # (x, y) coordinates of the second point on the original line
distance = 50  # Distance between the original line and the parallel line
extension_percentage = 0.2  # Extension percentage as a fraction of the offset distance

# Create a blank image
image = np.zeros((400, 400, 3), dtype=np.uint8)

# Calculate the coordinates of the points on the parallel line
#parallel_point1, parallel_point2 = draw_parallel_line(point1, point2, distance)

# Calculate the coordinates of the points on the extended parallel line
#extended_parallel_point1, extended_parallel_point2 = extend_line(parallel_point1, parallel_point2, extension_percentage)



# Calculate the coordinates of the points on the extended parallel line
extended_parallel_point1, extended_parallel_point2 = make_parallel_extend_line(point1, point2, distance, extension_percentage)



# Draw the original line
cv2.line(image, point1, point2, (255, 0, 0), 2)

# Draw the extended parallel line
cv2.line(image, extended_parallel_point1, extended_parallel_point2, (0, 0, 255), 2)

# Display the image
cv2.imshow("Parallel Line", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
