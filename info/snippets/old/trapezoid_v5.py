import cv2
import numpy as np

# Load the image
img = cv2.imread('your_image.jpg')

# Convert the image to grayscale
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Apply thresholding to convert the image to binary
ret, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

# Find the external contours in the image
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Create an empty array to hold the trapezoids
trapezoids = []

# Loop over the contours
for i in range(len(contours)):
    # Approximate the contour with a polygon of desired level of detail
    epsilon = 0.01 * cv2.arcLength(contours[i], True)
    approx = cv2.approxPolyDP(contours[i], epsilon, True)

    # Get the bounding rectangle of the polygon
    rect = cv2.boundingRect(approx)
    x, y, w, h = rect

    # Calculate the area of the polygon
    area = cv2.contourArea(approx)

    # Calculate the area of each trapezoid
    num_trapezoids = 10 # You can adjust this value to change the number of trapezoids
    trapezoid_area = area / num_trapezoids

    # Calculate the height of each trapezoid
    trapezoid_height = h / num_trapezoids

    # Calculate the top and bottom widths of each trapezoid
    top_width = w / 2
    bottom_width = w / 2

    # Loop over the trapezoids
    for j in range(num_trapezoids):
        # Calculate the y-coordinates of the top and bottom edges of the trapezoid
        y_top = y + j * trapezoid_height
        y_bottom = y_top + trapezoid_height

        # Calculate the x-coordinates of the left and right edges of the trapezoid
        x_left = x + (top_width - j * (top_width - bottom_width) / num_trapezoids)
        x_right = x + w - (top_width - j * (top_width - bottom_width) / num_trapezoids)

        # Add the trapezoid to the list of trapezoids
        trapezoid = np.array([[x_left, y_top], [x_right, y_top], [x_right, y_bottom], [x_left, y_bottom]], np.int32)
        trapezoids.append(trapezoid)

    # Draw the trapezoids on the original image
    cv2.drawContours(img, [approx], -1, (0, 0, 255), 2)
    for trap in trapezoids:
        cv2.drawContours(img, [trap], 0, (0, 255, 0), 2)

    # Reset the list of trapezoids for the next polygon
    trapezoids = []

# Display the image
cv2.imshow('image', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
