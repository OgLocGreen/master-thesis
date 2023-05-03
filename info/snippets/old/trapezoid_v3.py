import cv2
import numpy as np

importedImage = 'img_hulls_dilate.jpg'
originalImg = cv2.imread(importedImage)

#filters image bilaterally and displays it
bilatImg = cv2.bilateralFilter(originalImg, 5, 175, 175)

#finds edges of bilaterally filtered image and displays it
edgeImg = cv2.Canny(bilatImg, 75, 200)

#gets contours (outlines) for shapes and sorts from largest area to smallest area
contours, hierarchy = cv2.findContours(edgeImg, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
contours = sorted(contours, key=cv2.contourArea, reverse=True)

# drawing red contours on the image
for con in contours:
    cv2.drawContours(originalImg, con, -1, (0, 0, 255), 3)

# and double-checking the outcome
cv2.imshow("Contours check",originalImg)
cv2.waitKey()
cv2.destroyWindow("Contours check")

# find the perimeter of the first closed contour
perim = cv2.arcLength(contours[0], True)
# setting the precision
epsilon = 0.02*perim
# approximating the contour with a polygon
approxCorners = cv2.approxPolyDP(contours[0], epsilon, True)
# check how many vertices has the approximate polygon
approxCornersNumber = len(approxCorners)
print("Number of approximated corners: ", approxCornersNumber)

# can also be used to filter before moving on [if needed]
# i.e. if approxCornersNumber== 4:

# printing the position of the calculated corners
print("Coordinates of approximated corners:\n", approxCorners)