import cv2
import numpy as np

# Load an image
image = cv2.imread('contours.jpg', cv2.IMREAD_GRAYSCALE)

# Threshold the image
_, thresh = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY)

# Find contours in the thresholded image
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Create an empty mask for the result
mask_only_hull = np.zeros_like(image)

# Iterate through each contour
for contour in contours:
    # Get the bounding box of the contour
    x, y, w, h = cv2.boundingRect(contour)
    
    # Check if the contour is close to the border
    if x < 10 or y < 10 or x + w > image.shape[1] - 10 or y + h > image.shape[0] - 10:
        # Create a new contour that connects the contour to the border
        border_contour = np.array([
            [[0, 0]],
            [[0, image.shape[0]]],
            [[image.shape[1], image.shape[0]]],
            [[image.shape[1], 0]]
        ], dtype=np.int32)
        
        # Concatenate the border contour and the original contour
        new_contour = np.concatenate((border_contour, contour), axis=0)
        
        # Draw the new contour on the original image
        cv2.drawContours(mask_only_hull, [new_contour], 0, (0, 255, 0), 2)

# Display the result
cv2.imshow('Contours', mask_only_hull)
cv2.waitKey(0)
cv2.destroyAllWindows()