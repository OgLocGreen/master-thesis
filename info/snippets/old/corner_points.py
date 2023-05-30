import cv2
import numpy as np

def draw_trapezoid(image, points, color=(0, 255, 0), thickness=2):
    # Ensure that we have exactly four points
    if len(points) != 4:
        raise ValueError("Trapezoid should have exactly four points.")

    points = [[int(x), int(y)] for x, y in points]
    # Sort the points based on their y-coordinates
    sorted_points = sorted(points, key=lambda p: p[1])

    # Determine the top points and bottom points
    top_points = sorted(sorted_points[:2], key=lambda p: p[0])
    bottom_points = sorted(sorted_points[2:], key=lambda p: p[0])

    # Draw the trapezoid edges
    cv2.line(image, tuple(top_points[0]), tuple(top_points[1]), color, thickness)
    cv2.line(image, tuple(top_points[1]), tuple(bottom_points[1]), color, thickness)
    cv2.line(image, tuple(bottom_points[1]), tuple(bottom_points[0]), color, thickness)
    cv2.line(image, tuple(bottom_points[0]), tuple(top_points[0]), color, thickness)

    # Return the corner points
    top_left = top_points[0]
    top_right = top_points[1]
    bottom_left = bottom_points[0]
    bottom_right = bottom_points[1]

    return top_left, top_right, bottom_left, bottom_right

# Create a blank image
image = np.zeros((600, 600, 3), dtype=np.uint8)

# Define the trapezoid coordinates (in any order)
trapezoid = [[150, 150], [350, 200], [100, 500], [400, 400]]
#trapezoid = [[100, 100], [200, 100],[100, 200], [200, 200]]


trapezoid = [[179.468, 468.0], [179.468, 335.2288123481492], [189.331, 331.0], [189.331, 472.0052166307438]]



# Draw the trapezoid and get the corner points
top_left, top_right, bottom_left, bottom_right = draw_trapezoid(image, trapezoid)

# Show the image
cv2.imshow("Trapezoid", image)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Print the corner points
print("Top Left:", top_left)
print("Top Right:", top_right)
print("Bottom Left:", bottom_left)
print("Bottom Right:", bottom_right)