import numpy as np
import cv2


def corrdinates_to_pixel(x,y):
    x_pixel = 1654/14.9433
    y_pixel = 591/4.989820
    return x_pixel*x, 591-(y_pixel*y)

array = np.load('./snippets/array_2.npy')

image = cv2.imread('./snippets/result.png')



# Define the color in BGR (for yellow it's (0, 255, 255))
color = (0, 255, 255)
# Draw the points on the image

for point in array:
    x,y = corrdinates_to_pixel(point[0], point[1])
    point = [int(x), int(y)]
    cv2.circle(image, point, 3, color, -1)  # 5 is the radius of the circle, -1 means the circle will be filled

# Display the image
cv2.imshow('Image with yellow points', image)
cv2.waitKey(0)
cv2.destroyAllWindows()