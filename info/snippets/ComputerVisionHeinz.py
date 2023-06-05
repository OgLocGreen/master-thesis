import cv2
import numpy as np
import seidel as sd
import matplotlib.pyplot as plt
from scipy.ndimage import rotate
from scipy.ndimage.morphology import binary_dilation
from scipy.ndimage import binary_erosion

from info.snippets.matlab_algoritm_func_2_flascher import make_working_zones


def get_trapezoids(grouped_polygones_dilate_zones, img_dilate_polygone_zones, image):
    """
    Given grouped polygones and their corresponding images, calculate the trapezoids of each polygone.
    Args:
        grouped_polygones_dilate_zones (list): List of grouped polygones for each image.
        img_dilate_polygone_zones (list): List of cropped images for each polygone.
        image (ndarray): Original image.
    Returns:
        polygones_zones (list): List of trapezoids for each polygone.
    """
    polygones_zones = []
    for i, (gouped_polygones, image_cropped_polygones) in enumerate(zip(grouped_polygones_dilate_zones, img_dilate_polygone_zones)):
        trapezoids_list = []
        for polygone in gouped_polygones:
            if i == 0 or i == 1:
                array1 = [[float(x), float(y)] for point in polygone for x, y in point]
            if i == 2 or i == 3:
                array1 = [[float(y), float(x)] for point in polygone for x, y in point]

            # Convert the points to a NumPy array of shape (n,1,2)
            points_array = np.array([array1], dtype=np.int32)

            # Draw the polygon on the image
            image5 = np.copy(image)
            for point in array1:
                cv2.polylines(image5, [points_array], True, (0, 0, 255), thickness=2)

            # get trapzoid for each hull
            seidel1 = sd.Triangulator(array1)
            triangles = seidel1.triangles()
            trapezoids = seidel1.trapezoids

            trap = []
            for t in trapezoids:
                verts = t.vertices()
                trap.append(verts)

            # Changes from [[(x1,y1),(x2,y2),(x3,y3),(x4,y4)],[x1,y2].....] to [[[x1,y1],[x2,y2],[x3,y3],[x4,y4]],[[x1,y2].....]]
            image4 = np.zeros_like(image_cropped_polygones)
            trap_group = []
            for points_trap in trap:
                point_trap = []
                for x, y in points_trap:
                    if i == 0 or i == 1:
                        point_trap.append([float(x), float(y)])
                    if i == 2 or i == 3:
                        point_trap.append([float(y), float(x)])
                trap_group.append(point_trap)

            # Reshape array so it can be printed with opencv
            points_array = np.array([trap_group], dtype=np.int32)
            for point in trap_group:
                # Draw the polygon on the image
                # Reshape the array to have shape (1, n, 2)
                pts = np.array([point], np.int32)
                pts = pts.reshape((-1, 1, 2))
                cv2.polylines(image4, [pts], True, (0, 0, 255), thickness=2)

            # Add all trapezoids of one polygone to a list
            trapezoids_list.append(trap_group)

        polygones_zones.append(trapezoids_list)

    return polygones_zones

def dilate_polygons(img_list, orientations=[(20,1),(20,1),(20,1),(20,1)], threshold_detail_polygone = 0.025):
    """
    This function takes in a list of images, dilates each image using the dilate_image function, and then extracts 
    polygons from the dilated image using the get_hulls function. The dilated image, grouped polygons, and polygon 
    image are then appended to separate lists. 
    
    Args:
        img_list: A list of images to be dilated and polygonalized
        orientations: A list of tuples representing the kernel size for each image
        threshold_detail_polygone: A float representing the threshold for polygonalization
    
    Returns:
        image_dilate_zones: A list of dilated images
        grouped_polygones_dilate_zones: A list of grouped polygons extracted from the dilated images
        img_dilate_polygone_zones: A list of images with only polygons extracted from the dilated images
    """
    image_dilate_zones = []
    grouped_polygones_dilate_zones = []
    img_dilate_polygone_zones = []
    
    for img,orientation in zip(img_list, orientations):
        img_dilate = dilate_image(img, kernel_size = orientation)
        image_dilate_zones.append(img_dilate)
        grouped_hulls_dilate, img_hulls_dilate = get_hulls(img_dilate, threshold_detail_polygone = threshold_detail_polygone)
        grouped_polygones_dilate_zones.append(grouped_hulls_dilate)
        img_dilate_polygone_zones.append(img_hulls_dilate)
    
    return image_dilate_zones, grouped_polygones_dilate_zones, img_dilate_polygone_zones

def dilate_image(image, kernel_size=(20, 1), iterations=2):
    """
    Dilates the input image using a rectangular kernel.

    Args:
        image (numpy.ndarray): a numpy array representing the input image
        kernel_size (tuple[int, int]): the size of the rectangular kernel for dilation. Default is (20, 1)
        iterations (int): the number of times to apply the dilation operation. Default is 2

    Returns:
        dilated_image (numpy.ndarray): a numpy array representing the dilated image
    """

    # Define the kernel (structuring element) for dilation
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, kernel_size) # Create a rectangular kernel with the given size

    # Perform dilation on the image
    dilated_image = cv2.dilate(image, kernel, iterations=iterations) # Apply the dilation operation on the image

    return dilated_image

def get_hulls(image, working_zones=None, min_area=600, threshold_detail_polygone = 0.01, acceleration_offset = 0, threshold_border = 20):
    """
    Finds and draws the convex hulls of regions of interest in an image.

    Args:
        working_zones: a list of tuples, where each tuple contains two points representing opposite corners of a rectangle.
        image: a NumPy array representing an image.
        min_area: an integer representing the minimum area threshold for contours. Default is 600.
        threshold_detail_polygone: A float representing the threshold for polygonalization(detail of the polygone) Default is 0.01
    Returns:
        hull_group: a list of lists, where each inner list contains the points of the convex hulls of the regions of interest.
        image: a NumPy array representing the input image with the convex hulls drawn on it.
        images_iterations: a list of images after each iteration a pic was cropped out
    """
    hull_group = []
    images_cropped_polygones = []
    images_iterations = []
    if working_zones is None:
        # Get the contours and grouped contours in the cropped image
        grouped_contours, img_contour = get_grouped_contours(image=image,threshold_detail_polygone=threshold_detail_polygone, min_area=min_area)

        # Make the first hull closed
        hull_group, img_hull = make_first_hull_closed(grouped_contours, img_contour)

        # Connect the hull to the border of the image
        hull_group_with_edge, img_hull_border = make_hull_connected_to_border(hull_group, img_hull, threshold_border = 20)

        # Fill in the corners of the hull
        hull_group_with_corner, img_hull_corner = fill_corners(hull_group_with_edge, img_hull_border)

        # Extract the finished hull
        hull_finished, img_finished_hull = extract_finished_polynomes(img_hull_corner, threshold_detail_polygone = threshold_detail_polygone)

        return hull_finished, img_finished_hull
    else:
        # Loop over the working zones and find the convex hulls
        for i, z in enumerate(working_zones):
            if i == 0:
                # Crop the image to the current working zone
                img_cropped, image_deleted = get_rectangle(image, z[0], z[1],acceleration_offset)
            else:
                # Crop the image to the current working zone
                img_cropped, image_deleted = get_rectangle(image_deleted, z[0], z[1], acceleration_offset)

            images_iterations.append(image_deleted)

            # Get the contours and grouped contours in the cropped image
            grouped_contours, img_contour = get_grouped_contours(image=img_cropped,threshold_detail_polygone = threshold_detail_polygone, min_area=20)

            # Make the first hull closed
            hull_group, img_hull = make_first_hull_closed(grouped_contours, img_contour)

            # Connect the hull to the border of the image
            hull_group_with_edge, img_hull_border = make_hull_connected_to_border(hull_group, img_hull, threshold_border = threshold_border)    # TODO: check why when the point is to close to the boarder it does not work
                                                                                                                                                # vlt muss ich auch den alten algorithmus austauschen und auch wieder ein Dilation hinzufügen oder eb
                                                                                                                                                # diese checken letzter punkt in der liste bzw. weil ich aber ja nicht ob der letzte punkt immer der nähste an der aussen kannte ist      

            # Fill in the corners of the hull
            hull_group_with_corner, img_hull_corner = fill_corners(hull_group_with_edge, img_hull_border)

            # Extract the finished hull
            hull_finished, img_finished_hull = extract_finished_polynomes(img_hull_corner, threshold_detail_polygone = threshold_detail_polygone)

            # Get the starting and ending coordinates of the current working zone
            h, w = image.shape[:2]
            cx, cy = w // 2, h // 2
            x1, y1 = cx + z[0][0], cy + z[0][1]
            x2, y2 = cx + z[1][0], cy + z[1][1]
            x_start = min(x1, x2)
            x_end = max(x1, x2)
            y_start = min(y1, y2)
            y_end = max(y1, y2)


            image_black_cropped = np.zeros_like(img_cropped) # Top Left

            # Draw the hulls on the image with different colors for different working zones
            for hull in hull_finished:
                if i == 0:
                    x_start = x_start + acceleration_offset
                    x_end = x_end - acceleration_offset
                    cv2.drawContours(image[y_start:y_end, x_start:x_end], [hull], 0, (0, 0, 255), 2)
                    cv2.drawContours(image_black_cropped, [hull], 0, (255, 255, 255), 2)
                elif i == 1:
                    x_start = x_start + acceleration_offset
                    x_end = x_end - acceleration_offset
                    cv2.drawContours(image[y_start:y_end, x_start:x_end], [hull], 0, (0, 255, 0), 2)
                    cv2.drawContours(image_black_cropped, [hull], 0, (255, 255, 255), 2)
                elif i == 2:
                    y_start = y_start + acceleration_offset
                    y_end = y_end - acceleration_offset
                    cv2.drawContours(image[y_start:y_end, x_start:x_end], [hull], 0, (255, 0, 0), 2)
                    cv2.drawContours(image_black_cropped, [hull], 0, (255, 255, 255), 2)
                elif i == 3:
                    y_start = y_start + acceleration_offset
                    y_end = y_end - acceleration_offset
                    cv2.drawContours(image[y_start:y_end, x_start:x_end], [hull], 0, (0, 255, 255), 2)
                    cv2.drawContours(image_black_cropped, [hull], 0, (255, 255, 255), 2)

            # append the finished hull for this working zone to the hull group list
            hull_group.append(hull_finished)
            images_cropped_polygones.append(image_black_cropped)

        return hull_group, image, images_cropped_polygones, images_iterations

def get_rectangle(image, point1, point2,acceleration_offset=0, direction = 0):
    """
    Get a rectangle from the input image defined by point1 and point2.
    Args:
        image (numpy.ndarray): The input image as a NumPy array.
        point1 (tuple): The first point defining the top-left corner of the rectangle as (x, y) coordinates.
        point2 (tuple): The second point defining the bottom-right corner of the rectangle as (x, y) coordinates.
        acceleration_offset (int): The offset to the acceleration point. Makes the Working area smaller.
        direction (int): The direction of the rectangle. 0 = horizontal, 1 = vertical.

    Returns:
        numpy.ndarray: The cropped image within the rectangle.
        numpy.ndarray: Orginal image with a black mask over the cropped rectangle.
    """
    h, w = image.shape[:2] # Get height and width of the image
    cx, cy = w // 2, h // 2 # Calculate center coordinates

    # Calculate actual coordinates of the corner points based on center coordinates
    x1, y1 = cx + point1[0], cy + point1[1]
    x2, y2 = cx + point2[0], cy + point2[1]
    
    
    # Ensure the points are sorted in ascending order and add the acceleration offset so the cropped working area is smaller
    if direction == 0 or direction == 1:
        x_start = min(x1, x2) + acceleration_offset
        x_end = max(x1, x2) -  acceleration_offset
        y_start = min(y1, y2)
        y_end = max(y1, y2)
    else:
        x_start = min(x1, x2)
        x_end = max(x1, x2)
        y_start = min(y1, y2) + acceleration_offset
        y_end = max(y1, y2) - acceleration_offset
    

    # Crop the image to the rectangle defined by the points
    cropped_image = image[y_start:y_end, x_start:x_end]

    # Ensure the points are sorted in ascending order dont mask the working area + acceleration offset
    # just the working area so other working areas later could do that 
    x_start = min(x1, x2)
    x_end = max(x1, x2)
    y_start = min(y1, y2)
    y_end = max(y1, y2)

    mask = cv2.rectangle(image.copy(), (x_start, y_start), (x_end, y_end), (0,0,0), -1)
    
    cv2.imshow("mask", mask)
    cv2.imshow("cropped_image", cropped_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


    return cropped_image, mask

def get_grouped_contours(image, threshold_detail_polygone, min_area=600):
    """
    Get grouped contours from an input image.

    Args:
        image (numpy.ndarray): Input image
        min_area (int, optional): Minimum area threshold to filter out small contours. Defaults to 600.

    Returns:
        grouped_contours (list): A list of grouped contours
        img_contour (numpy.ndarray): The input image with the grouped contours drawn on it
    """

    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Apply image thresholding
    _, thresh = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY)

    # Find contours in the image
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Create an empty mask for the result
    img_contour = np.zeros_like(image)

    # Create an empty list to store grouped contours
    grouped_contours = []

    # Iterate over all found contours
    for contour in contours:
        # Calculate the perimeter of the contour
        perimeter = cv2.arcLength(contour, True)

        # Approximate the contour to a closed contour with fewer corners
        epsilon = threshold_detail_polygone * perimeter
        approx = cv2.approxPolyDP(contour, epsilon, True)

        # Calculate the area of the contour
        area = cv2.contourArea(contour)

        # Filter out contours with small area (e.g. text)
        if area >= min_area and len(approx) >= 3:
            # Draw the contour in white on the mask
            cv2.drawContours(img_contour, [contour], 0, (255, 255, 255), 2)

            # Add the contour to the grouped contours list
            grouped_contours.append(contour)

    return grouped_contours, img_contour

def make_first_hull_closed(grouped_contours, image):
    """
    Make the first hull a closed contour and draw it on the input image.

    Args:
        grouped_contours (list): List of grouped contours
        image (numpy.ndarray): Input image

    Returns:
        list: Grouped hull contours
        numpy.ndarray: Image with the first hull contour drawn on it
    """
    # Number the grouped hull contours
    hull_group = []

    # Create a copy of the input image to draw the hulls on
    img_hull = np.zeros_like(image)

    # Number the grouped contours
    for i in range(len(grouped_contours)):
        # Convert the contour to a closed line
        hull = cv2.convexHull(grouped_contours[i])
        hull_group.append(hull)
        cv2.drawContours(img_hull, [hull], 0, (0, 0, 255), 2)

    return hull_group, img_hull

def make_hull_connected_to_border(grouped_hulls, image, threshold_border=30):
    """
    Make the convex hulls connected to the image border and fill them.

    Args:
        grouped_hulls (list): List of convex hulls
        image (numpy.ndarray): Input image
        threshold (int): Threshold distance to the image border (default: 20)

    Returns:
        list: Grouped convex hulls with edges connected to the border
        numpy.ndarray: Image with the updated convex hulls drawn and filled
    """

    # Draw the new convex hulls on a black image
    img_hull_border = np.zeros_like(image)

    hull_group_with_edge = []

    # Iterate over all hulls in the hull group    
    for hull in grouped_hulls:
        # Extract the edges from the convex hull
        edges = []
        edges2 = []
        edges3 = []
        for i in range(len(hull) - 1):
            edges.append((tuple(hull[i][0]), tuple(hull[i + 1][0])))
        edges.append((tuple(hull[-1][0]), tuple(hull[0][0])))
     
        # Update vertices of edges close to the border
        for i, edge in enumerate(edges):
            updated_edge = []
            updated_edge2 = []
            updated_edge3 = []
            for vertex in edge:
                x, y = vertex
                x1, y1 = None, None
                updated_edge3.append((x, y))
                if x < threshold_border:
                    x = 0
                    x1 = 0
                elif x >= image.shape[1] - threshold_border:
                    x = image.shape[1] - 1
                    x1 = image.shape[1] - 1
                if y < threshold_border:
                    y = 0
                    y1 = 0
                elif y >= image.shape[0] - threshold_border:
                    y = image.shape[0] - 1
                    y1 = image.shape[0] - 1
                updated_edge.append((x, y))
                if x1 != None or y1 != None:
                    if x1 == None:
                        x1 = x
                    if y1 == None:
                        y1 = y
                    updated_edge2.append((x1, y1))
            edges[i] = tuple(updated_edge)
            edges3.append(tuple(updated_edge3))
            if updated_edge2 != []:
                if len(updated_edge2) == 1:
                    updated_edge2.append(updated_edge2[0])
                edges2.append(tuple(updated_edge2))

        if edges2 != []:
            edges4 = edges2[::-1]
            for edge in edges4:
                edges3.append(edge)

        # Create a black image
        img = np.zeros_like(image)

        # Draw each edge on the image
        for edge in edges3:
            cv2.line(img, edge[0], edge[1], (255, 255, 255), 2)

        # Create a new convex hull from the updated edges
        hull_from_edges = cv2.convexHull(np.array(edges3).reshape(-1, 2), clockwise=False)

        # Add the hull to the hull group
        hull_group_with_edge.append(hull_from_edges)

        # Draw the hull on the image
        cv2.drawContours(img_hull_border, [hull_from_edges], 0, 255, 2)
    return hull_group_with_edge, img_hull_border

def fill_corners(hull_goup_with_edge, image):
    """
    Check if a corner is close, if yes, fill all of the corner.

    Args:
        image (numpy.ndarray): Input image.
        hull_goup_with_edge (list): List of convex hulls with edges.

    Returns:
        img_hull_corner (numpy.ndarray): Output image with filled corners.
        new_group_all (list): List of updated convex hulls.
    """
    # Extract the edges from the convex hull
    # edge are always between two points
    # i dont know why but it works like that
    # [(x1,y2),(x2,y2)]

    # here we search for connections with the border
    # if it is connected to 2 sides 
    # then add a point at the corner
    # [(0,0),(0,0)]
    img_hull_corner = np.zeros_like(image)

    new_group_all = []
    
    for i, hull in enumerate(hull_goup_with_edge):

        # Extract the edges from the convex hull
        edges = []
        for i in range(len(hull) - 1):
            edges.append((tuple(hull[i][0]), tuple(hull[i + 1][0])))
        edges.append((tuple(hull[-1][0]), tuple(hull[0][0])))
        edges2 = edges.copy()
        for i, edge in enumerate(edges):
            new_edge = []
            left, right, top, bottom = False, False, False, False
            for vertex in edge:
                x,y = vertex
                if x == 0:
                    left = True
                if x == image.shape[1] - 1:
                    right = True
                if y == 0:
                    top = True 
                if y == image.shape[0] - 1:
                    bottom = True
                if left and top and len(new_edge) <2:
                    new_edge.append((0,0))
                    new_edge.append((0,0))
                if left and bottom and len(new_edge) <2:
                    new_edge.append((0,image.shape[0] - 1))
                    new_edge.append((0,image.shape[0] - 1))
                if right and top and len(new_edge) <2:
                    new_edge.append((image.shape[1] - 1,0))
                    new_edge.append((image.shape[1] - 1,0))
                if right and bottom and len(new_edge) <2:
                    new_edge.append((image.shape[1] - 1,image.shape[0] - 1))
                    new_edge.append((image.shape[1] - 1,image.shape[0] - 1))
            if new_edge != []:
                edges2.append(tuple(new_edge))

        # Create a new convex hull from the updated edges
        hull_from_edges = cv2.convexHull(np.array(edges2).reshape(-1, 2), clockwise=False)
            # Add the hull to the hull group
        new_group_all.append(hull_from_edges)
        # Draw the hull on the image
        cv2.drawContours(img_hull_corner, [hull_from_edges], 0,(255,255,255), 2)

    # Return the output image and the updated convex hulls
    return new_group_all, img_hull_corner

def extract_finished_polynomes(img_hull_corner, threshold_detail_polygone = 0.025):
    '''
    Extracts the finished convex hull from the input image with filled corners.

    Args:
        img_hull_corner (numpy array): Input image with filled corners.
        threshold_detail_polygone (float): Threshold for the detail of the polygone.
    Returns:
        finished_hull (numpy array): Image with only the contour of the convex hulls.
    '''

    # Convert the image to grayscale
    gray = cv2.cvtColor(img_hull_corner, cv2.COLOR_BGR2GRAY)

    # Threshold the grayscale image to create a binary image
    _, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

    # Find contours in the binary image
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # make hull
    hulls = [cv2.convexHull(contour) for contour in contours]


    # make poly out of hull
    polys = [cv2.approxPolyDP(hull, threshold_detail_polygone * cv2.arcLength(hull, True), True) for hull in hulls]

    # Create a copy of the input image to draw the hulls on
    img_finished_hull = np.zeros_like(img_hull_corner)


    # Draw the convex hulls around the contours
    for polygone in polys:

        # Approximate the convex hull with a polygon
        cv2.drawContours(img_finished_hull, [polygone], 0, (255, 255, 255), 2)

    return polys, img_finished_hull

def make_working_zones_old(\
        image, h_c = int(591/2), l_c = int(1654/2), y_d = 30, x_d = 55, h_r = 25, l_r = 50):
    '''
    Creates working zones based on the input image dimensions and specified parameters.

    Args:
        image (numpy array): Original input image.

    Returns:
        z0 (list): Zone 0 coordinates as [(x1, y1), (x2, y2)].
        z90 (list): Zone 90 coordinates as [(x1, y1), (x2, y2)].
        z180 (list): Zone 180 coordinates as [(x1, y1), (x2, y2)].
        z270 (list): Zone 270 coordinates as [(x1, y1), (x2, y2)].
    '''

    # Needed variables
    h_c = int(image.shape[0]/2)      # Hälfte der Breite des Blechs entspricht der Höhe des Bildes
    l_c = int(image.shape[1]/2)     # Hälfte der Länge des Blechs entspricht der Breite des Bildes
    y_d = 30                # Abstand y der Kamera vom Mittelpunkt des Robots
    x_d = 50                # Abstand x der Kamera vom Mittelpunkt des Robots
    h_r = 25                 # Hälfte der Breite des Robots
    l_r = 50                 # Hälfte der Länge zwischen den Rädern des Robots

    # Zone 0
    x1 = -(l_c-(max(l_r, -x_d)+ x_d))
    y1 = -(h_c-(max(h_r, -y_d)+ y_d))
    x2 = l_c-max(l_r, x_d)+ x_d
    y2 = h_c-max(h_r, y_d)+ y_d
    z0 = [(x1,y1),(x2,y2)]

    # Zone 90
    x1 = -(l_c-(max(h_r, y_d)- y_d))
    y1 = -(h_c-(max(l_r, -x_d)+ x_d))
    x2 = l_c-max(h_r, -y_d)- y_d
    y2 = h_c-max(l_r, x_d)+ x_d
    z90 = [(x1,y1),(x2,y2)]

    # Zone 180
    x1 = -(l_c-(max(l_r, x_d)- x_d))
    y1 = -(h_c-(max(h_r, y_d)- y_d))
    x2 = l_c-max(l_r, -x_d)- x_d    
    y2 = h_c-max(h_r, -y_d)- y_d
    z180 = [(x1,y1),(x2,y2)]

    # Zone 270
    x1 = -(l_c-(max(h_r, -y_d)+ y_d))
    y1 = -(h_c-(max(l_r, x_d)- x_d))
    x2 = l_c-max(h_r, y_d)+ y_d
    y2 = h_c-max(l_r, -x_d)- x_d
    z270 = [(x1,y1),(x2,y2)]

    return z0, z90, z180, z270

if __name__ == '__main__':

    # Load the image
    image = cv2.imread('panorama.png')

    # Check if the image was loaded successfully
    if image is None:
        print("Error: Failed to load the image.")
        exit()
    threshold_detail_polygone = 0.005

    # Get the contours and a black Image with the contours drawn on it
    grouped_contours, image_contours = get_grouped_contours(image,  threshold_detail_polygone, min_area=600,)

    # Make the first hull closed
    grouped_hulls, image_hulls = make_first_hull_closed(grouped_contours, image_contours)

    # Connect the hull to the border of the image
    grouped_hulls_border, image_hulls_border = make_hull_connected_to_border(grouped_hulls, image_hulls, threshold_border = 20)

    # Fill in the corners of the hulls
    grouped_hulls_edges, image_hulls_corner = fill_corners(grouped_hulls_border, image_hulls_border)

    # Extract the finished hull
    grouped_polynones_finished, image_finished_polynome = extract_finished_polynomes(image_hulls_corner)

    # Claculate the working zones like in the paper
    z0, z90, z180, z270 = make_working_zones(image=image_finished_polynome)
    working_zones = [z0, z90, z180, z270]

    #For now its a mock up
    h, w = image.shape[:2]
    h, w = image.shape[0], image.shape[1]
    h, w = int(h/2), int(w/2)
    z0 = [(0,0),(w,h)]
    z90 = [(0,0),(-w,-h)]
    z180 = [(0,0),(-w,h)]
    z270 = [(0,0),(w,-h)]
    working_zones_mockup = [z0, z90, z180, z270]

    #working_zones = working_zones_mockup
    print(working_zones)

    for i, zone in enumerate(working_zones):
        print("zone: ", i)
        print(zone)
        x1, y1 = zone[0]
        x2, y2 = zone[1]

        x1 = x1 + w
        y1 = y1 + h
        x2 = x2 + w
        y2 = y2 + h

        print("x1, y1: ", x1, y1)
        print("x2, y2: ", x2, y2)

    # Define the threshold for the detail of the polygone
    threshold_detail_polygone = 0.005

    # extract the hulls of each working zone
    hull_finished_working_zones, img_finished_hull_working_zones, img_list_zones, images_iterations = \
    get_hulls(image_hulls_corner, working_zones, min_area = 10, threshold_detail_polygone=threshold_detail_polygone, threshold_border = 20)

    kernel = [(20,1),(20,1),(1,20),(1,20)]

    # make the dilate of each polygone in each working zone
    image_dilate_zones, grouped_polygones_dilate_zones, img_dilate_polygone_zones = \
    dilate_polygons(img_list_zones,kernel , threshold_detail_polygone=threshold_detail_polygone)

    # make the trapezoids of each polygone in each working zone
    polygones_zones = get_trapezoids(grouped_polygones_dilate_zones, img_dilate_polygone_zones, image)

    # show the trapezoids
    for polygone_groups, image_cropped_polygones in zip(polygones_zones,img_list_zones):
        image5 = np.zeros_like(image_cropped_polygones)
        for polygone in polygone_groups:
            for trap in polygone:
                # Draw the polygon on the image
                # Reshape the array to have shape (1, n, 2)
                pts = np.array([trap], np.int32)
                pts = pts.reshape((-1, 1, 2))
                cv2.polylines(image5, [pts], True, (0, 0, 255), thickness=2)
        #cv2.imshow("image5", image5)
        #cv2.waitKey(0)
        #cv2.destroyAllWindows()

    
    ### Open Points
    # FIXME: old idears check at the end of master thesis
    # Change how to connecto to the Border (Maybe Check for last and first point and connect them to the Border)

    # !!! Check the Working zones

    # the dilation some times is bigger then the borders
    # so the problem is that sometimes we only can scan a part of the zone
    # this could be a problem for edges of the working zones
    # because somethimes they could overlap

    # Option 1:
    # theoretical we could scan the same part twice
    # for scaning fine but not for repairing

    # Option 2:
    # check if the contour complete inside a working zone
    # check if the contour is after the dilation still in the contour
    # decide if its better for better zone 
    # to divide the zone in two zones or more
    # or scan like in option 1

    # so we need to check if the dilation is bigger then the orginal image

   
    # show the images
    cv2.imshow("image", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()



