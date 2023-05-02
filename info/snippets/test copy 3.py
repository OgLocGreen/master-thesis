import cv2
import numpy as np

# Create an empty image
img = np.zeros((500, 500), dtype=np.uint8)

# Draw a rectangle on the image
cv2.rectangle(img, (100, 100), (400, 300), 255, thickness=-1)

# Get the contours of the rectangle
contours, _ = cv2.findContours(img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Set the width threshold
width_thresh = 20

# Calculate the number of trapezoids based on the rectangle width
rect_width = 300
num_trapezoids = int(np.ceil(rect_width / width_thresh))

# Calculate the width of each trapezoid
trapezoid_width = rect_width / num_trapezoids

# Loop through the trapezoids
for i in range(num_trapezoids):
    # Calculate the x-coordinates of the trapezoid
    x1 = int(100 + i * trapezoid_width)
    x2 = int(x1 + trapezoid_width)
    
    # Calculate the y-coordinates of the trapezoid
    y1 = 100
    y2 = 300
    
    # Calculate the width of the top and bottom of the trapezoid
    top_width = trapezoid_width / 2
    bottom_width = trapezoid_width
    
    # Calculate the height of the trapezoid
    height = y2 - y1
    
    # Calculate the vertices of the trapezoid
    vertices = np.array([(x1 + top_width, y1),
                         (x1, y2),
                         (x2, y2),
                         (x2 - top_width, y1)],
                        dtype=np.int32)
    
    # Draw the trapezoid on the image
    cv2.drawContours(img, [vertices], 0, 127, thickness=-1)

# Display the image
cv2.imshow('image', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
