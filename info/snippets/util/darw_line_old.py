import cv2
import numpy as np

# Create a blank image
image = np.ones((500, 500, 3), np.uint8) * 255

def draw_stripes(image, angle, stripe_distance, color=(0, 0, 0)):
    # If the angle is between 90 and 180, flip the direction of the lines
    if 90 <= angle < 180:
        angle -= 180
        stripe_distance = -stripe_distance

    # Calculate the direction of the stripes
    direction = np.array([np.cos(np.radians(angle)), np.sin(np.radians(angle))])

    # Get the size of the image
    height, width = image.shape[:2]

    # Calculate the number of stripes needed to cover the image diagonally
    num_stripes = int(np.ceil(np.hypot(height, width) / stripe_distance))

    # Calculate the start position of the first stripe
    start_pos = np.array([width / 2 - direction[0] * stripe_distance * num_stripes / 2,
                          height - direction[1] * stripe_distance * num_stripes / 2])

    for i in range(num_stripes):
        # Calculate the start and end points of the stripe
        start_point = start_pos + direction * stripe_distance * i
        print(start_point)
        end_point = start_point + direction * np.array([width, height])
        print(end_point)
        cv2.line(image, tuple(start_point.astype(int)), tuple(end_point.astype(int)), color, 1)
        break

# Draw stripes at a certain angle
draw_stripes(image, 45, 20)

# Display the image
cv2.imshow('Image', image)
cv2.waitKey(0)
cv2.destroyAllWindows()
