import cv2

# Load the image
image = cv2.imread('image.jpg', cv2.IMREAD_GRAYSCALE)

# Find contours in the image
contours, _ = cv2.findContours(image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Set the threshold for closeness to the border
threshold = 50

# Loop through each contour
for contour in contours:
    # Find the bounding rectangle for the contour
    x, y, w, h = cv2.boundingRect(contour)

    # Check if the contour is close to the top border
    if y < threshold:
        # Dilate the contour to the top border
        cv2.drawContours(image, [cv2.convexHull(contour)], 0, 255, -1)
        cv2.drawContours(image, [cv2.convexHull(contour)], 0, 0, 2)

    # Check if the contour is close to the bottom border
    if y + h > image.shape[0] - threshold:
        # Dilate the contour to the bottom border
        cv2.drawContours(image, [cv2.convexHull(contour)], 0, 255, -1)
        cv2.drawContours(image, [cv2.convexHull(contour)], 0, 0, 2)

    # Check if the contour is close to the left border
    if x < threshold:
        # Dilate the contour to the left border
        cv2.drawContours(image, [cv2.convexHull(contour)], 0, 255, -1)
        cv2.drawContours(image, [cv2.convexHull(contour)], 0, 0, 2)

    # Check if the contour is close to the right border
    if x + w > image.shape[1] - threshold:
        # Dilate the contour to the right border
        cv2.drawContours(image, [cv2.convexHull(contour)], 0, 255, -1)
        cv2.drawContours(image, [cv2.convexHull(contour)], 0, 0, 2)

# Display the result
cv2.imshow('Result', image)
cv2.waitKey(0)
cv2.destroyAllWindows()
