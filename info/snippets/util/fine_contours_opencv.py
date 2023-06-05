import cv2
import numpy as np
import matplotlib.pyplot as plt

# Create a sample binary image with two objects
image = np.ones((200, 200), dtype=np.uint8)
#cv2.rectangle(image, (30, 30), (70, 70), 255, -1)
#cv2.circle(image, (120, 120), 50, 255, -1)

# Find contours in the binary image
contours, _ = cv2.findContours(image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Create a new figure for visualization
plt.figure(figsize=(6, 6))
plt.imshow(image, cmap='gray')

# Plot the detected contours
for contour in contours:
    # Reshape contour to (N, 2) array
    contour = contour.reshape(-1, 2)
    # Plot contour points
    plt.plot(contour[:, 0], contour[:, 1], 'r', linewidth=2)

# Set axis limits and show the plot
plt.xlim(0, image.shape[1])
plt.ylim(image.shape[0], 0)
plt.axis('off')
plt.show()


points = contour
# Extract x and y coordinates from the points array
x = points[:,  0]
y = points[:, 1]

# Plot the lines between points
plt.plot(x, y, 'b-')

# Show the plot
plt.show()
