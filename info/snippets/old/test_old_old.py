import cv2
import numpy as np

def draw_line(img, start_point, angle, color=(255, 255, 255), thickness=1):
    # Find the height and width of the image
    height, width = img.shape[:2]

    # Convert the angle to radians
    angle_rad = np.deg2rad(angle)


    #Draw line to one side
    # Find the end point of the line, based on the given angle
    end_point_x = int(start_point[0] + np.sin(angle_rad) * width)
    end_point_y = int(start_point[1] + np.cos(angle_rad) * height)


    if end_point_x > width or end_point_y > height:
        if end_point_x < width:
            end_point_x = width

        if end_point_y < height:
            end_point_y = height
        
        img2 = np.zeros((end_point_x, end_point_y, 3), dtype=np.uint8)


        # Convert to integer
        end_point = (int(end_point_x), int(end_point_y))

        img2[0: width, 0: height] = img
        # Draw the line on the image
        img2 = cv2.line(img2, start_point, end_point, color, thickness)

        img = img2[0: width, 0: height]
    else:
        # Draw the line on the image
        img = cv2.line(img, start_point, end_point, color, thickness)


    return img


def compute_center_of_mass(points):
    x_coords = [p[0] for p in points]
    y_coords = [p[1] for p in points]
    centroid_x = int(sum(x_coords) / len(points))
    centroid_y = int(sum(y_coords) / len(points))
    return (centroid_x, centroid_y)





from snippets.old.PathPlaningNormal_reworked import get_corner

# Draw the trapezoid, line, and intersections
img = np.zeros((500, 500, 3), dtype=np.uint8)

# Define the trapezoid
trapezoid = [[100, 150],[350, 200], [100, 450], [400, 400]]

top_left_point, top_right_point, bottom_left_point, bottom_right_point = get_corner(trapezoid)


trapezoid2 = [[top_left_point, top_right_point],
                [bottom_left_point, bottom_right_point],
                [bottom_left_point, top_left_point],
                [bottom_right_point, top_right_point]]


for side in trapezoid2:
    cv2.line(img, (int(side[0][0]), int(side[0][1])), (int(side[1][0]), int(side[1][1])), (0, 0, 255), 1)




start_point = compute_center_of_mass(trapezoid)
angle = 45  # replace with your angle
img = draw_line(img, start_point, angle)

angle = 20  # replace with your angle
img = draw_line(img, start_point, angle)


angle = 90  # replace with your angle
img = draw_line(img, start_point, angle)

cv2.imshow('Image with line', img)
cv2.waitKey(0)
cv2.destroyAllWindows()