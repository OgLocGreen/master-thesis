import cv2
import numpy as np

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


# Example usage
point1 = (50, 100)  # (x, y) coordinates of the first point on the original line
point2 = (350, 300)  # (x, y) coordinates of the second point on the original line
distance = 50  # Distance between the original line and the parallel line

# Create a blank image
image = np.zeros((400, 400, 3), dtype=np.uint8)

# Draw the parallel line
parallel_point1, parallel_point2 = draw_parallel_line(point1, point2, distance)



# Draw the original line
cv2.line(image, point1, point2, (255, 0, 0), 2)

# Draw the parallel line
cv2.line(image, parallel_point1, parallel_point2, (0, 0, 255), 2)


# Display the image
cv2.imshow("Parallel Line", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
