import cv2
import numpy as np
import seidel as sd
import matplotlib.pyplot as plt

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

def get_trapezoids_gpt(grouped_polygons_dilate_zones, img_dilate_polygon_zones, image):
    """
    Given grouped polygons and their corresponding images, calculate the trapezoids of each polygon.
    Args:
        grouped_polygons_dilate_zones (list): List of grouped polygons for each image.
        img_dilate_polygon_zones (list): List of cropped images for each polygon.
        image (ndarray): Original image.
    Returns:
        trapezoids_polygons_zones (list): List of trapezoids for each polygon.
    """
    # Create an empty list to hold the trapezoids
    trapezoids_polygons_zones = []

    # Iterate over grouped_polygons_dilate_zones and img_dilate_polygon_zones simultaneously
    for i, (gouped_polygons, image_cropped_polygons) in enumerate(zip(grouped_polygons_dilate_zones, img_dilate_polygon_zones)):

        # Create a list to hold the trapezoids for each polygon
        trapezoids_list = []

        # Iterate over each polygon in the group
        for polygon in gouped_polygons:

            # Convert the point's coordinates from (x, y) to (y, x) based on the index i
            if i == 0 or i == 1:
                array1 = [[float(x), float(y)] for point in polygon for x, y in point]
            if i == 2 or i == 3:
                array1 = [[float(y), float(x)] for point in polygon for x, y in point]

            # Convert the list of points to a numpy array
            points_array = np.array([array1], dtype=np.int32)

            # Copy the original image
            image5 = np.copy(image)

            # Draw the polygon on the copied image
            for point in array1:
                cv2.polylines(image5, [points_array], True, (0, 0, 255), thickness=2)

            # Use Seidel's algorithm to triangulate the polygon
            seidel1 = sd.Triangulator(array1)
            triangles = seidel1.triangles()
            trapezoids = seidel1.trapezoids

            # Extract the vertices of the trapezoids
            trap = [[float(x), float(y)] for t in trapezoids for x, y in t.vertices()]

            # Create an empty image of the same size as image_cropped_polygons
            image4 = np.zeros_like(image_cropped_polygons)

            # Convert the list of points to the required format for cv2.polylines
            trap_group = []
            for x,y in trap:
                point_trap = []
                if i == 0 or i == 1:
                    point_trap.append([float(x), float(y)])
                if i == 2 or i == 3:
                    point_trap.append([float(y), float(x)])
                trap_group.append(point_trap)

            # Convert the list of points to a numpy array
            points_array = np.array([trap_group], dtype=np.int32)

            # Draw the polygons on the image
            for point in trap_group:
                pts = np.array([point], np.int32)
                pts = pts.reshape((-1, 1, 2))
                cv2.polylines(image4, [pts], True, (0, 0, 255), thickness=2)

            # Add the trapezoids to the list
            trapezoids_list.append(trap_group)

        # Add the list of trapezoids to the final list
        trapezoids_polygons_zones.append(trapezoids_list)

    # Return the final list of trapez
    return trapezoids_polygons_zones

def dilate_polygons(img_list, orientations=[(20,1),(20,1),(20,1),(20,1)], threshold_detail_polygon = 0.025):
    """
    This function takes in a list of images, dilates each image using the dilate_image function, and then extracts 
    polygons from the dilated image using the get_hulls function. The dilated image, grouped polygons, and polygon 
    image are then appended to separate lists. 
    
    Args:
        img_list: A list of images to be dilated and polygonalized
        orientations: A list of tuples representing the kernel size for each image
        threshold_detail_polygon: A float representing the threshold for polygonalization
    
    Returns:
        image_dilate_zones: A list of dilated images
        grouped_polygons_dilate_zones: A list of grouped polygons extracted from the dilated images
        img_dilate_polygon_zones: A list of images with only polygon extracted from the dilated images
    """
    image_dilate_zones = []
    grouped_polygons_dilate_zones = []
    img_dilate_polygon_zones = []
    
    for img,orientation in zip(img_list, orientations):
        img_dilate = dilate_image(img, kernel_size = orientation)
        image_dilate_zones.append(img_dilate)
        grouped_hulls_dilate, img_hulls_dilate = get_hulls(img_dilate, threshold_detail_polygon = threshold_detail_polygon)
        grouped_polygons_dilate_zones.append(grouped_hulls_dilate)
        img_dilate_polygon_zones.append(img_hulls_dilate)
    
    return image_dilate_zones, grouped_polygons_dilate_zones, img_dilate_polygon_zones

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

def get_hulls(image, working_zones=None, min_area=600, threshold_detail_polygon = 0.01, acceleration_offset = 0, threshold_border = 20):
    """
    Finds and draws the convex hulls of regions of interest in an image.

    Args:
        working_zones: a list of tuples, where each tuple contains two points representing opposite corners of a rectangle.
        image: a NumPy array representing an image.
        min_area: an integer representing the minimum area threshold for contours. Default is 600.
        threshold_detail_polygon: A float representing the threshold for polygonalization(detail of the polygon) Default is 0.01
    Returns:
        hull_group: a list of lists, where each inner list contains the points of the convex hulls of the regions of interest.
        image: a NumPy array representing the input image with the convex hulls drawn on it.
        images_iterations: a list of images after each iteration a pic was cropped out
    """
    hull_group = []
    images_cropped_polygons = []
    images_iterations = []
    image_zeros = np.zeros_like(image)
    if working_zones is None:
        # Get the contours and grouped contours in the cropped image
        grouped_contours, img_contour = get_grouped_contours(image=image,threshold_detail_polygon=threshold_detail_polygon, min_area=min_area)

        # Make the first hull closed
        hull_group, img_hull = make_first_hull_closed(grouped_contours, img_contour)

        # Connect the hull to the border of the image
        hull_group_with_edge, img_hull_border = make_hull_connected_to_border(hull_group, img_hull, threshold_border = threshold_border)

        # Fill in the corners of the hull
        hull_group_with_corner, img_hull_corner = fill_corners(hull_group_with_edge, img_hull_border)

        # Extract the finished hull
        hull_finished, img_finished_hull = extract_finished_polynomes(img_hull_corner, threshold_detail_polygon = threshold_detail_polygon)

        return hull_finished, img_finished_hull
    else:
        # Loop over the working zones and find the convex hulls
        for i, z in enumerate(working_zones):
            if i == 0:
                # Crop the image to the current working zone
                img_cropped, image_deleted = get_rectangle(image, z[0], z[1],acceleration_offset)
                print("img_cropped shape", img_cropped.shape)
                print("image_zeros shape", image_zeros.shape)
                print("z[0]", z[0])
                print("z[1]", z[1])
                img_cropped = make_complete(image_zeros, z[0], z[1], img_cropped, acceleration_offset=acceleration_offset)
            else:
                # Crop the image to the current working zone
                img_cropped, image_deleted = get_rectangle(image_deleted, z[0], z[1], acceleration_offset)
                img_cropped = make_complete(image_zeros, z[0], z[1], img_cropped, acceleration_offset=acceleration_offset)

            images_iterations.append(image_deleted)

            # Get the contours and grouped contours in the cropped image
            grouped_contours, img_contour = get_grouped_contours(image=img_cropped,threshold_detail_polygon = threshold_detail_polygon, min_area=20)

            # Make the first hull closed
            hull_group, img_hull = make_first_hull_closed(grouped_contours, img_contour)

            # Connect the hull to the border of the image
            hull_group_with_edge, img_hull_border = make_hull_connected_to_border(hull_group, img_hull, threshold_border = threshold_border)    # TODO: check why when the point is to close to the boarder it does not work
                                                                                                                                                # vlt muss ich auch den alten algorithmus austauschen und auch wieder ein Dilation hinzufügen oder eb
                                                                                                                                                # diese checken letzter punkt in der liste bzw. weil ich aber ja nicht ob der letzte punkt immer der nähste an der aussen kannte ist      

            # Fill in the corners of the hull
            hull_group_with_corner, img_hull_corner = fill_corners(hull_group_with_edge, img_hull_border)

            # Extract the finished hull
            hull_finished, img_finished_hull = extract_finished_polynomes(img_hull_corner, threshold_detail_polygon = threshold_detail_polygon)

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
            images_cropped_polygons.append(image_black_cropped)

        return hull_group, image, images_cropped_polygons, images_iterations


def get_hulls_gpt(image, working_zones=None, min_area=600, threshold_detail_polygon = 0.01, acceleration_offset = 0, threshold_border = 20):
    """
    Find and draw the convex hulls of the regions of interest in an image.

    Args:
        image (numpy.ndarray): The input image.
        working_zones (list of tuple): A list of working zones, where each zone is a tuple of two points that define a rectangle.
        min_area (int): The minimum contour area to be considered.
        threshold_detail_polygon (float): The approximation accuracy for the Ramer-Douglas-Peucker algorithm. This is the maximum distance from contour to approximated polygon.
        acceleration_offset (int): The offset added to the points of the rectangle to shrink the working area.
        threshold_border (int): The minimum distance from a contour to the image border for it to be considered connected to the border.

    Returns:
        hull_group (list of list): A list of all the convex hulls, where each hull is a list of points.
        image (numpy.ndarray): The original image with the convex hulls drawn on it.
        images_iterations (list of numpy.ndarray): The list of images after each working zone was processed.
    """

    # The list of all convex hulls
    hull_group = []

    # A copy of the image with all pixels set to zero
    image_zeros = np.zeros_like(image)

    # If no working zones are specified, process the entire image
    if working_zones is None:
        # Get the contours and grouped contours in the image
        grouped_contours, img_contour = get_grouped_contours(image=image, threshold_detail_polygon=threshold_detail_polygon, min_area=min_area)

        # Make the first hull closed
        hull_group, img_hull = make_first_hull_closed(grouped_contours, img_contour)

        # Connect the hull to the border of the image
        hull_group_with_edge, img_hull_border = make_hull_connected_to_border(hull_group, img_hull, threshold_border=threshold_border)

        # Fill in the corners of the hull
        hull_group_with_corner, img_hull_corner = fill_corners(hull_group_with_edge, img_hull_border)

        # Extract the finished hull
        hull_finished, img_finished_hull = extract_finished_polynomes(img_hull_corner, threshold_detail_polygon=threshold_detail_polygon)

        return hull_finished, img_finished_hull

    else:
        # If working zones are specified, process each working zone individually
        for i, z in enumerate(working_zones):
            if i == 0:
                # Crop the image to the current working zone
                img_cropped, image_deleted = get_rectangle(image, z[0], z[1], acceleration_offset)
                img_cropped = make_complete(image_zeros, z[0], z[1], img_cropped)
            else:
                # Crop the remaining part of the image to the current working zone
                img_cropped, image_deleted = get_rectangle(image_deleted, z[0], z[1], acceleration_offset)
                img_cropped = make_complete(image_zeros, z[0], z[1], img_cropped)

            # Add the image with the current working zone removed to the list of iteration images
            images_iterations.append(image_deleted)

            # Process the cropped image in the same way as when no working zones are specified

            # ...

            # After processing the cropped image, draw the convex hulls on the original image, using a different color for each working zone
            # Note: You are currently drawing the hulls on the working zones, not on the entire image

            # ...

        return hull_group, image, images_cropped_polygons, images_iterations


def make_complete(image, point1, point2, cropped_image, acceleration_offset=0, direction=0):
    """
    Replace a rectangular region in an image with another image (cropped_image), defined by two points.

    Args:
        image (numpy.ndarray): The original image.
        point1 (tuple): The first point defining the top-left corner of the rectangle (relative to the center of the image).
        point2 (tuple): The second point defining the bottom-right corner of the rectangle (relative to the center of the image).
        cropped_image (numpy.ndarray): The image to be placed in the defined rectangle.
        acceleration_offset (int): The offset to shrink the rectangle region from its sides.
        direction (int): The orientation of the rectangle. 0 for horizontal, 1 for vertical.

    Returns:
        numpy.ndarray: The updated image with the cropped_image in the defined rectangular region.
    """

    # Get the dimensions of the image
    h, w = image.shape[:2]

    # Calculate the coordinates of the center of the image
    cx, cy = w // 2, h // 2

    # Convert the input points from relative to absolute coordinates
    x1, y1 = cx + point1[0], cy + point1[1]
    x2, y2 = cx + point2[0], cy + point2[1]

    # Determine the start and end coordinates of the rectangle region,
    # adding the acceleration offset to make the working area smaller
    if direction == 0 or direction == 1:
        x_start = min(x1, x2) + acceleration_offset
        x_end = max(x1, x2) - acceleration_offset
        y_start = min(y1, y2)
        y_end = max(y1, y2)
    else:
        x_start = min(x1, x2)
        x_end = max(x1, x2)
        y_start = min(y1, y2) + acceleration_offset
        y_end = max(y1, y2) - acceleration_offset

    print(y_start,y_end, x_start,x_end)

    # Replace the rectangle region in the original image with the cropped_image
    image[y_start:y_end, x_start:x_end] = cropped_image

    # Return the updated image
    return image

    
def get_rectangle(image, point1, point2, acceleration_offset=0, direction = 0):
    """
    Extracts a rectangular region from an image defined by two points and masks this region in the original image.

    Args:
        image (numpy.ndarray): The input image as a NumPy array.
        point1 (tuple): The first point defining the top-left corner of the rectangle (relative to the center of the image).
        point2 (tuple): The second point defining the bottom-right corner of the rectangle (relative to the center of the image).
        acceleration_offset (int): The offset to shrink the rectangle region from its sides.
        direction (int): The orientation of the rectangle. 0 for horizontal, 1 for vertical.

    Returns:
        numpy.ndarray: The extracted rectangle region from the image.
        numpy.ndarray: The original image with the extracted rectangle region blacked out.
    """

    # Get the dimensions of the image
    h, w = image.shape[:2] 

    # Calculate the coordinates of the center of the image
    cx, cy = w // 2, h // 2 

    # Convert the input points from relative to absolute coordinates
    x1, y1 = cx + point1[0], cy + point1[1]
    x2, y2 = cx + point2[0], cy + point2[1]
    
    # Determine the start and end coordinates of the rectangle region,
    # adding the acceleration offset to make the working area smaller.
    if direction == 0 or direction == 1:
        x_start = min(x1, x2) + acceleration_offset
        x_end = max(x1, x2) - acceleration_offset
        y_start = min(y1, y2)
        y_end = max(y1, y2)
    else:
        x_start = min(x1, x2)
        x_end = max(x1, x2)
        y_start = min(y1, y2) + acceleration_offset
        y_end = max(y1, y2) - acceleration_offset

    # Crop the rectangle region from the image
    cropped_image = image[y_start:y_end, x_start:x_end]

    # Determine the start and end coordinates of the rectangle region for masking, without the acceleration offset
    x_start = min(x1, x2)
    x_end = max(x1, x2)
    y_start = min(y1, y2)
    y_end = max(y1, y2)

    # Create a mask by drawing a filled rectangle on a copy of the image
    mask = cv2.rectangle(image.copy(), (x_start, y_start), (x_end, y_end), (0, 0, 0), -1)
    
    # Display the mask and the cropped image for debugging
    cv2.imshow("mask", mask)
    cv2.imshow("cropped_image", cropped_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Return the cropped image and the mask
    return cropped_image, mask

def get_grouped_polygon(image, threshold_detail_polygon=0.05 , min_area=600):
    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Threshold the grayscale image to create a binary image
    _, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

    # Find contours in the binary image
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # make hull
    hulls = [cv2.convexHull(contour) for contour in contours]


    # make poly out of hull
    polys = [cv2.approxPolyDP(hull, threshold_detail_polygon * cv2.arcLength(hull, True), True) for hull in hulls]

    

def get_grouped_contours(image, threshold_detail_polygon=0.05 , min_area=600):
    """
    This function extracts and groups contours from an input image.

    Args:
        image (numpy.ndarray): Input image in BGR format.
        threshold_detail_polygon (float): Threshold to control the accuracy of the polygonal approximation.
        min_area (int, optional): Minimum area threshold to filter out small contours. Defaults to 600.

    Returns:
        list: A list of grouped contours. Each contour is a numpy array of (x,y) coordinates of boundary points.
        numpy.ndarray: An image with the grouped contours drawn on it.
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

        # Approximate the contour to a closed polygon with fewer vertices
        epsilon = threshold_detail_polygon * perimeter
        approx = cv2.approxPolyDP(contour, epsilon, True)

        # Calculate the area of the contour
        area = cv2.contourArea(contour)

        # Filter out contours with small area (e.g. text, noise)
        if area >= min_area and len(approx) >= 3:
            # Draw the contour in white on the mask
            white_color = (255, 255, 255)
            contours_line_thickness = 2
            cv2.drawContours(img_contour, [contour], -1, white_color, contours_line_thickness)

            # Add the contour to the grouped contours list
            grouped_contours.append(contour)

    return grouped_contours, img_contour

def make_first_hull_closed(grouped_contours, image):
    """
    Converts each contour in the provided list to a convex hull, which is a closed contour. 
    Each hull is then drawn on a copy of the input image.

    Args:
        grouped_contours (list): List of grouped contours
        image (numpy.ndarray): Input image

    Returns:
        list: List of convex hulls derived from the input contours
        numpy.ndarray: Image with the convex hulls drawn on it
    """
    # Initialize an empty list to store the convex hulls
    hull_group = []

    # Create a copy of the input image to draw the hulls on
    img_hull = np.zeros_like(image)

    # Iterate through each contour in the provided list
    for i in range(len(grouped_contours)):
        # Convert the contour to a closed convex hull
        hull = cv2.convexHull(grouped_contours[i])

        # Add the convex hull to the list
        hull_group.append(hull)

        # Draw the convex hull on the image in red color
        cv2.drawContours(img_hull, [hull], 0, (0, 0, 255), 2)

    # Return the list of convex hulls and the image with the convex hulls drawn
    return hull_group, img_hull


def make_hull_connected_to_border(grouped_hulls, image, threshold_border=30):
    """
    Make the convex hulls connected to the image border and fill them.

    Args:
        grouped_hulls (list): List of convex hulls
        image (numpy.ndarray): Input image
        threshold_border (int): Threshold distance to the image border (default: 30)

    Returns:
        list: Grouped convex hulls with edges connected to the border
        numpy.ndarray: Image with the updated convex hulls drawn and filled
    """

    # Initialize a black image to draw the updated convex hulls
    img_hull_border = np.zeros_like(image)

    # Create an empty list to store hulls connected to image border
    hull_group_with_edge = []

    # Iterate over all hulls in the hull group    
    for hull in grouped_hulls:
        # Extract the edges from the convex hull
        edges = []
        for i in range(len(hull) - 1):
            edges.append((tuple(hull[i][0]), tuple(hull[i + 1][0])))
        edges.append((tuple(hull[-1][0]), tuple(hull[0][0])))
     
        # Initialize a list for edges after modification
        updated_edges = []

        # Update vertices of edges close to the border
        for i, edge in enumerate(edges):
            updated_edge = []
            for vertex in edge:
                x, y = vertex
                # If x or y is less than threshold from border, set it to 0
                # If x or y is more than threshold from the other border, set it to max value
                if x < threshold_border:
                    x = 0
                elif x >= image.shape[1] - threshold_border:
                    x = image.shape[1] - 1
                if y < threshold_border:
                    y = 0
                elif y >= image.shape[0] - threshold_border:
                    y = image.shape[0] - 1

                # Append updated vertices to updated_edge list
                updated_edge.append((x, y))

            # Update the current edge with updated_edge
            edges[i] = tuple(updated_edge)

            # Add updated_edge to updated_edges list
            updated_edges.extend(updated_edge)

        # Create a new convex hull from the updated edges
        hull_from_edges = cv2.convexHull(np.array(updated_edges).reshape(-1, 2), clockwise=False)

        # Add the hull to the hull group
        hull_group_with_edge.append(hull_from_edges)

        # Draw the hull on the image
        cv2.drawContours(img_hull_border, [hull_from_edges], 0, 255, 2)
    return hull_group_with_edge, img_hull_border

def fill_corners(hull_group_with_edge, image, image_input):
    """
    Checks if a hull corner is close to the image border. If it is, it fills the corner.

    Args:
        image (numpy.ndarray): Input image.
        hull_group_with_edge (list): List of convex hulls with edges connected to the image border.

    Returns:
        img_hull_corner (numpy.ndarray): Output image with filled corners.
        new_group_all (list): List of updated convex hulls.
    """

    # Create a blank copy of the input image
    img_hull_corner = np.zeros_like(image)

    # Initialize a list to store the new hulls
    new_group_all = []

    # Iterate over all hulls in the group
    for i, hull in enumerate(hull_group_with_edge):
        # Initialize a list to store the hull edges
        edges = []

        # Create tuples representing each edge in the hull
        for i in range(len(hull) - 1):
            edges.append((tuple(hull[i][0]), tuple(hull[i + 1][0])))
        edges.append((tuple(hull[-1][0]), tuple(hull[0][0])))
        
        edges2 = edges.copy()

        # Iterate over all edges
        for i, edge in enumerate(edges):
            # Initialize an empty list for the new edge and flag variables for each border
            new_edge = []
            left, right, top, bottom = False, False, False, False

            # Check each vertex in the edge
            for vertex in edge:
                x, y = vertex

                # Check if the vertex is close to the border
                if x == 0:
                    left = True
                if x == image.shape[1] - 1:
                    right = True
                if y == 0:
                    top = True
                if y == image.shape[0] - 1:
                    bottom = True

                # If the vertex is close to two borders, add a point at the corner
                if left and top and len(new_edge) < 2:
                    new_edge.append((0, 0))
                    new_edge.append((0, 0))
                if left and bottom and len(new_edge) < 2:
                    new_edge.append((0, image.shape[0] - 1))
                    new_edge.append((0, image.shape[0] - 1))
                if right and top and len(new_edge) < 2:
                    new_edge.append((image.shape[1] - 1, 0))
                    new_edge.append((image.shape[1] - 1, 0))
                if right and bottom and len(new_edge) < 2:
                    new_edge.append((image.shape[1] - 1, image.shape[0] - 1))
                    new_edge.append((image.shape[1] - 1, image.shape[0] - 1))

            # If a new edge was created, add it to the edge list
            if new_edge != []:
                edges2.append(tuple(new_edge))

        # Create a new convex hull from the updated edges
        hull_from_edges = cv2.convexHull(np.array(edges2).reshape(-1, 2), clockwise=False)

        # Add the new hull to the hull group
        new_group_all.append(hull_from_edges)

        # Draw the new hull on the image
        cv2.drawContours(img_hull_corner, [hull_from_edges], 0, (255, 255, 255), 2)
        cv2.drawContours(image_input, [hull_from_edges], 0, (0, 0, 255), 2)
    # Return the output image and the list of new hulls
    return new_group_all, img_hull_corner, image_input


def extract_finished_polynomes(img_hull_corner, threshold_detail_polygon = 0.025):
    '''
    Extracts the finished convex hull from the input image with filled corners.

    Args:
        img_hull_corner (numpy array): Input image with filled corners.
        threshold_detail_polygon (float): Threshold for the detail of the polygon.
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
    polys = [cv2.approxPolyDP(hull, threshold_detail_polygon * cv2.arcLength(hull, True), True) for hull in hulls]

    # Create a copy of the input image to draw the hulls on
    img_finished_polygon = np.zeros_like(img_hull_corner)


    # Draw the convex hulls around the contours
    for polygon in polys:

        # Approximate the convex hull with a polygon
        cv2.drawContours(img_finished_polygon, [polygon], 0, (255, 255, 255), 2)

    return polys, img_finished_polygon

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
    image = cv2.imread('../info/snippets/panorama.png')
    #image = cv2.flip(image, 0)
    # Check if the image was loaded successfully
    if image is None:
        print("Error: Failed to load the image.")
        exit()
    threshold_detail_polygon = 0.005

    # shape orignal pic (591, 1654)
    # shape pic(535, 1554)

    # Get the contours and a black Image with the contours drawn on it
    grouped_contours, image_contours = get_grouped_contours(image,  threshold_detail_polygon, min_area=600,)

    # Make the first hull closed
    grouped_hulls, image_hulls = make_first_hull_closed(grouped_contours, image_contours)

    # Connect the hull to the border of the image
    grouped_hulls_border, image_hulls_border = make_hull_connected_to_border(grouped_hulls, image_hulls, threshold_border = 20)

    # Fill in the corners of the hulls
    grouped_hulls_edges, image_hulls_corner = fill_corners(grouped_hulls_border, image_hulls_border)

    # Extract the finished hull
    grouped_polynones_finished, image_finished_polynome = extract_finished_polynomes(image_hulls_corner)
    
    text_color = (0, 255, 255)
    for polyngom in grouped_polynones_finished:
        for points in polyngom:
            for label, (x,y) in enumerate(points):
                cv2.putText(image_finished_polynome, str(str(x) +"," + str(y)), (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2, cv2.LINE_AA)
    #image_finished_polynome_fliped = cv2.flip(image_finished_polynome, 0)
    #cv2.imshow('image_finished_polynome_fliped', image_finished_polynome_fliped)
    cv2.imshow('image_finished_polynome', image_finished_polynome)
    cv2.waitKey(0)  


    poly = []
    for i, polygon in enumerate(grouped_polynones_finished):
        zone = []
        for k, point in enumerate(polygon):
            for one_point in point:
                test = polygon
                zone.append([one_point[0], one_point[1]])
        poly.append(zone)

    # Claculate the working zones like in the paper
    z0, z90, z180, z270 = make_working_zones_old(image=image_finished_polynome)
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

    # Define the threshold for the detail of the polygon
    threshold_detail_polygon = 0.005

    # extract the hulls of each working zone
    hull_finished_working_zones, img_finished_hull_working_zones, img_list_zones, images_iterations = \
    get_hulls(image_hulls_corner, working_zones, min_area = 10, threshold_detail_polygon=threshold_detail_polygon, threshold_border = 20)

    kernel = [(20,1),(20,1),(1,20),(1,20)]

    # make the dilate of each polygon in each working zone
    image_dilate_zones, grouped_polygons_dilate_zones, img_dilate_polygon_zones = \
    dilate_polygons(img_list_zones,kernel , threshold_detail_polygon=threshold_detail_polygon)

    test = np.array(grouped_polygons_dilate_zones[0])
    np.save("pts.npy", test)


    # make the trapezoids of each polygon in each working zone
    polygons_zones = get_trapezoids(grouped_polygons_dilate_zones, img_dilate_polygon_zones, image)

    image_test = image.copy()
    # show the trapezoids
    for polygon_groups, image_cropped_polygons in zip(polygons_zones,img_list_zones):
        image5 = np.zeros_like(image_cropped_polygons)
        for polygon in polygon_groups:
            for trap in polygon:
                # Draw the polygon on the image
                # Reshape the array to have shape (1, n, 2)
                pts = np.array([trap], np.int32)
                pts = pts.reshape((-1, 1, 2))

                cv2.polylines(image_test, [pts], True, (0, 0, 255), thickness=2)
        cv2.imshow("image5", image_test)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    
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



