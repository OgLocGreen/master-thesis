import cv2
import numpy as np

# Function to create trapezoids from rectangle contours
def create_trapezoids(contours, threshold):
    trapezoids = []
    for cnt in contours:
        # Get the minimum area rectangle
        rect = cv2.minAreaRect(cnt)
        box = cv2.boxPoints(rect)
        box = np.int0(box)
        # Calculate the width of the rectangle
        width = np.linalg.norm(box[0]-box[1])
        # Create trapezoid only if the width is greater than threshold
        if width > threshold:
            # Rearrange the points to create the trapezoid
            pts = np.array([box[1], box[0], box[3], box[2]], dtype=np.float32)
            # Add the trapezoid to the list
            trapezoids.append(pts)
    return trapezoids


def make_trapezoid2(img, width, width_threshold, num_trapezoids):
    num_trapezoids = calculate_num_trapezoids(width, width_threshold)
    h, w = img.shape[:2]
    trapezoid_width = (width - (num_trapezoids - 1) * width_threshold) / num_trapezoids
    trapezoids = []
    for i in range(num_trapezoids):
        x_start = int(i * (trapezoid_width + width_threshold))
        x_end = int(x_start + trapezoid_width)
        pts = np.array([(x_start, 0), (x_end, 0), (w - 1, h - 1), (0, h - 1)], dtype=np.int32)
        trapezoid = cv2.drawContours(np.zeros_like(img), [pts], -1, (255, 255, 255), -1)
        trapezoids.append(trapezoid)
    return trapezoids

def calculate_num_trapezoids(rectangle_width, trapezoid_width_threshold):
    num_trapezoids = int(rectangle_width / trapezoid_width_threshold)
    if num_trapezoids < 1:
        num_trapezoids = 1
    return num_trapezoids


# Load the image
image = cv2.imread('panorama.png')

# Create an empty mask for the result
image = np.zeros_like(image)

# Draw a rectangle on the image
start_point = (100, 100)
end_point = (400, 300)
color = (255, 255, 255)
thickness = 2
cv2.rectangle(image, start_point, end_point, color, thickness)

# Convert the image to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Apply binary threshold to get a binary image
ret, thresh = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)

# Find contours in the binary image
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Create trapezoids from the rectangle contours
trapezoids = make_trapezoid2(contours, threshold=100)

# Draw the trapezoids on the image
for trapezoid in trapezoids:
    cv2.drawContours(image, [trapezoid.astype(int)], 0, (255, 0, 0), thickness=10)

# Show the image
cv2.imshow('image', image)
cv2.waitKey(0)
cv2.destroyAllWindows()
