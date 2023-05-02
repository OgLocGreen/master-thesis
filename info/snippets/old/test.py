import cv2

def enhance_blue_channel(image):
    """
    Enhance the blue channel of the image to make it more blue.
    Args:
        image (numpy.ndarray): The input image as a NumPy array.
    Returns:
        numpy.ndarray: The image with enhanced blue channel.
    """
    # Split the image into its color channels
    b, g, r = cv2.split(image)
    
    # Enhance the blue channel
    b_enhanced = cv2.add(b, 30)  # You can adjust the value 30 to change the level of blue enhancement
    
    # Merge the enhanced blue channel back into the image
    enhanced_image = cv2.merge((b_enhanced, g, r))
    
    return enhanced_image

def apply_rectangle(image, point1, point2):
    """
    Apply a rectangle to the input image defined by point1 and point2, and enhance the blue channel.
    Args:
        image (numpy.ndarray): The input image as a NumPy array.
        point1 (tuple): The first point defining the top-left corner of the rectangle as (x, y) coordinates.
        point2 (tuple): The second point defining the bottom-right corner of the rectangle as (x, y) coordinates.
    Returns:
        numpy.ndarray: The modified image with the rectangle applied and blue channel enhanced.
        tuple: The new coordinates of the center point in the original image.
    """
    x1, y1 = point1
    x2, y2 = point2
    # Ensure the points are sorted in ascending order
    x_start = min(x1, x2)
    x_end = max(x1, x2)
    y_start = min(y1, y2)
    y_end = max(y1, y2)
    
    # Crop the image to the rectangle defined by the points
    cropped_image = image[y_start:y_end, x_start:x_end]
    
    # Draw a circle with center point (50, 100) within the cropped region
    circle_center = (50, 100)
    cv2.circle(cropped_image, circle_center, 10, (0, 0, 255), -1)  # You can adjust the circle parameters as needed
    
    # Enhance the blue channel of the cropped region
    enhanced_cropped_image = enhance_blue_channel(cropped_image)
    
    # Paste the cropped and enhanced region back onto the original image
    image[y_start:y_end, x_start:x_end] = enhanced_cropped_image
    
    # Calculate the new coordinates of the center point in the original image
    new_center_point = (circle_center[0] + x_start, circle_center[1] + y_start)
    
    return image, new_center_point

# Load the original image
image = cv2.imread('panorama.png')

# Set the points to define the rectangle
point1 = (100, 100)  # Top-left corner
point2 = (400, 400)  # Bottom-right corner

# Apply the rectangle, draw a circle, and enhance the blue channel
modified_image, new_center_point = apply_rectangle(image, point1, point2)

# Save the modified image
cv2.imwrite('modified_image.jpg', modified_image)

# Display the modified image
cv2.imshow('Modified Image', modified_image)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Print the new coordinates of the center point in the original image
print
