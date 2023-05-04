import cv2
import numpy as np
import array

import seidel
import matplotlib.pyplot as plt
from descartes import PolygonPatch
from shapely.geometry import  Polygon

def dilate_image(image, kernel_size=(20, 1), iterations=2):
    """
    Dilates the input image using a rectangular kernel.

    Args:
    - image (numpy.ndarray): a numpy array representing the input image
    - kernel_size (tuple[int, int]): the size of the rectangular kernel for dilation. Default is (20, 1)
    - iterations (int): the number of times to apply the dilation operation. Default is 2

    Returns:
    - dilated_image (numpy.ndarray): a numpy array representing the dilated image
    """

    # Define the kernel (structuring element) for dilation
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, kernel_size) # Create a rectangular kernel with the given size

    # Perform dilation on the image
    dilated_image = cv2.dilate(image, kernel, iterations=iterations) # Apply the dilation operation on the image

    return dilated_image

def get_hulls(image, working_zones=None, min_area=600):
    """
    Finds and draws the convex hulls of regions of interest in an image.

    Args:
    - working_zones: a list of tuples, where each tuple contains two points representing opposite corners of a rectangle.
    - image: a NumPy array representing an image.
    - min_area: an integer representing the minimum area threshold for contours. Default is 600.

    Returns:
    - hull_group: a list of lists, where each inner list contains the points of the convex hulls of the regions of interest.
    - image: a NumPy array representing the input image with the convex hulls drawn on it.
    """
    hull_group = []
    if working_zones is None:
        # Get the contours and grouped contours in the cropped image
        grouped_contours, img_contour = get_grouped_contours(image=image, min_area=min_area)

        # Make the first hull closed
        hull_group, img_hull = make_first_hull_closed(grouped_contours, img_contour)

        # Connect the hull to the border of the image
        hull_group_with_edge, img_hull_border = make_hull_connected_to_border(hull_group, img_hull)

        # Fill in the corners of the hull
        hull_group_with_corner, img_hull_corner = fill_corners(hull_group_with_edge, img_hull_border)

        # Extract the finished hull
        hull_finished, img_finished_hull = extract_finished_hull(img_hull_corner)

        return hull_finished, img_finished_hull
    else:
            
        # Loop over the working zones and find the convex hulls
        for i, z in enumerate(working_zones):
            # Crop the image to the current working zone
            img_cropped = get_rectangle(image, z[0], z[1])

            # Get the contours and grouped contours in the cropped image
            grouped_contours, img_contour = get_grouped_contours(image=img_cropped, min_area=min_area)

            # Make the first hull closed
            hull_group, img_hull = make_first_hull_closed(grouped_contours, img_contour)

            # Connect the hull to the border of the image
            hull_group_with_edge, img_hull_border = make_hull_connected_to_border(hull_group, img_hull)

            # Fill in the corners of the hull
            hull_group_with_corner, img_hull_corner = fill_corners(hull_group_with_edge, img_hull_border)

            # Extract the finished hull
            hull_finished, img_finished_hull = extract_finished_hull(img_hull_corner)

            # Get the starting and ending coordinates of the current working zone
            h, w = image.shape[:2]
            cx, cy = w // 2, h // 2
            x1, y1 = cx + z[0][0], cy + z[0][1]
            x2, y2 = cx + z[1][0], cy + z[1][1]
            x_start = min(x1, x2)
            x_end = max(x1, x2)
            y_start = min(y1, y2)
            y_end = max(y1, y2)

            # Draw the hulls on the image with different colors for different working zones
            for hull in hull_finished:
                if i == 0:
                    cv2.drawContours(image[y_start:y_end, x_start:x_end], [hull], 0, (0, 0, 255), 4)
                elif i == 1:
                    cv2.drawContours(image[y_start:y_end, x_start:x_end], [hull], 0, (0, 255, 0), 4)
                elif i == 2:
                    cv2.drawContours(image[y_start:y_end, x_start:x_end], [hull], 0, (255, 0, 0), 4)
                elif i == 3:
                    cv2.drawContours(image[y_start:y_end, x_start:x_end], [hull], 0, (0, 255, 255), 4)

            # append the finished hull for this working zone to the hull group list
            hull_group.append(hull_finished)

        return hull_group, image # return the list of hulls and the modified image


def get_rectangle(image, point1, point2):
    """
    Get a rectangle from the input image defined by point1 and point2.
    Args:
        image (numpy.ndarray): The input image as a NumPy array.
        point1 (tuple): The first point defining the top-left corner of the rectangle as (x, y) coordinates.
        point2 (tuple): The second point defining the bottom-right corner of the rectangle as (x, y) coordinates.
    Returns:
        numpy.ndarray: The cropped image within the rectangle.
    """
    h, w = image.shape[:2] # Get height and width of the image
    cx, cy = w // 2, h // 2 # Calculate center coordinates
    
    # Calculate actual coordinates of the corner points based on center coordinates
    x1, y1 = cx + point1[0], cy + point1[1]
    x2, y2 = cx + point2[0], cy + point2[1]
    
    # Ensure the points are sorted in ascending order
    x_start = min(x1, x2)
    x_end = max(x1, x2)
    y_start = min(y1, y2)
    y_end = max(y1, y2)
    
    # Crop the image to the rectangle defined by the points
    cropped_image = image[y_start:y_end, x_start:x_end]
    
    return cropped_image

def get_grouped_contours(image, min_area=600):
    """
    Get grouped contours from an input image.

    Args:
        image (numpy.ndarray): Input image
        min_area (int, optional): Minimum area threshold to filter out small contours. Defaults to 1000.

    Returns:
        list: Grouped contours
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
        epsilon = 0.01 * perimeter
        approx = cv2.approxPolyDP(contour, epsilon, True)

        # Calculate the area of the contour
        area = cv2.contourArea(contour)

        # Filter out contours with small area (e.g. text)
        if area >= min_area and len(approx) >= 3:
            # Draw the contour in white on the mask
            cv2.drawContours(img_contour, [contour], 0, (255, 255, 255), -1)

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
    img_hull = np.copy(image)

    # Number the grouped contours
    for i in range(len(grouped_contours)):
        # Convert the contour to a closed line
        hull = cv2.convexHull(grouped_contours[i])
        hull_group.append(hull)
        cv2.drawContours(img_hull, [hull], 0, (0, 0, 255), 4)

    return hull_group, img_hull

def make_hull_connected_to_border(grouped_hulls, image, threshold=20):
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
        for i in range(len(hull) - 1):
            edges.append((tuple(hull[i][0]), tuple(hull[i + 1][0])))
        edges.append((tuple(hull[-1][0]), tuple(hull[0][0])))

        # Update vertices of edges close to the border
        for i, edge in enumerate(edges):
            updated_edge = []
            for vertex in edge:
                x, y = vertex
                if x < threshold:
                    x = 0
                elif x >= image.shape[1] - threshold:
                    x = image.shape[1] - 1
                if y < threshold:
                    y = 0
                elif y >= image.shape[0] - threshold:
                    y = image.shape[0] - 1
                updated_edge.append((x, y))
            edges[i] = tuple(updated_edge)

        # Create a new convex hull from the updated edges
        hull_from_edges = cv2.convexHull(np.array(edges).reshape(-1, 2), clockwise=False)

        # Add the hull to the hull group
        hull_group_with_edge.append(hull_from_edges)

        # Draw the hull on the image
        cv2.drawContours(img_hull_border, [hull_from_edges], 0, 255, -1)
    
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


def extract_finished_hull(img_hull_corner):
    '''
    Extracts the finished convex hull from the input image with filled corners.

    Args:
        img_hull_corner (numpy array): Input image with filled corners.

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
    polys = [cv2.approxPolyDP(hull, 0.01 * cv2.arcLength(hull, True), True) for hull in hulls]

    # Create a copy of the input image to draw the hulls on
    img_finished_hull = np.zeros_like(img_hull_corner)


    # Draw the convex hulls around the contours
    for polygone in polys:

        # Approximate the convex hull with a polygon
        cv2.drawContours(img_finished_hull, [polygone], 0, (255, 255, 255), 4)

    return polys, img_finished_hull


def make_working_zones(image):
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
    x_d = 55                # Abstand x der Kamera vom Mittelpunkt des Robots
    h_r = 25                 # Hälfte der Breite des Robots
    l_r = 50                 # Hälfte der Länge zwischen den Rädern des Robots

    # Zone 0
    x1 = -(l_c-(max(l_r, -x_d)+ x_d))
    y1 = -(h_c-(max(h_r, -y_d)+ y_d))
    x2 = (l_c-(max(l_r, x_d)+ x_d))
    y2 = (h_c-(max(h_r, y_d)+ y_d))
    z0 = [(x1,y1),(x2,y2)]

    # Zone 90
    x1 = -(l_c-(max(h_r, y_d)- y_d))
    y2 = -(h_c-(max(l_r, -x_d)+ x_d))
    x2 = (l_c-(max(h_r, -y_d)- y_d))
    y2 = (h_c-(max(l_r, x_d)+ x_d))
    z90 = [(x1,y1),(x2,y2)]

    # Zone 180
    x1 = -(l_c-(max(l_r, x_d)- x_d))
    y1 = -(h_c-(max(h_r, y_d)- y_d))
    x2 = (l_c-(max(l_r, -x_d)- x_d))   # Hier ist ein Fehler, da x2 größer als 100 ist und unsere Plate nur 100 breit ist. Somit ist diese Zone außerhalb der Plate.
    y2 = (h_c-(max(h_r, -y_d)- y_d))
    z180 = [(x1,y1),(x2,y2)]

    # Zone 270
    x1 = -(l_c-(max(h_r, -y_d)+ y_d))
    y1 = -(h_c-(max(l_r, x_d)- x_d))
    x2 = (l_c-(max(h_r, y_d)+ y_d))
    y2 = (h_c-(max(l_r, -x_d)- x_d))
    z270 = [(x1,y1),(x2,y2)]

    return z0, z90, z180, z270


if __name__ == '__main__':

    # Load the image
    image = cv2.imread('panorama.png')

    # Check if the image was loaded successfully
    if image is None:
        print("Error: Failed to load the image.")
        exit()


    # make from the filled hullwith border and corner only the contour (finished_hull)
    hull_finished, img_finished_hull = get_hulls(image)


    # make the working zones
    #z0, z90, z180, z270 = make_working_zones(image)


    # make fake working zones
    h, w = image.shape[:2]
    h, w = int(h/2), int(w/2)
    z0 = [(0,0),(w,h)]
    z90 = [(0,0),(-w,-h)]
    z180 = [(0,0),(-w,h)]
    z270 = [(0,0),(w,-h)]
    working_zones = [z0, z90, z180, z270]

    # make the hulls for each working zone
    img_finished_hull2 = np.copy(img_finished_hull)
    hull_finished_working_zones1, img_finished_hull_working_zones1 = get_hulls(img_finished_hull2, working_zones, min_area = 200)

    image2 = np.copy(image)
    hull_finished_working_zones2, img_finished_hull_working_zones2 = get_hulls(image2, working_zones)


    # for the dilte image i need to have the a pic for each working area
    # then dilate each image and get the contours againg
    # then add the picture together -> or make out of these counturs 
    # the code below is just for all contours and not for each in the right direction
    # problem maybe we can just delay the conturs/hulls both diractions 
    # like it would get not just bigger to the left but also ro the right
    # same with up and down
    
    # exmapl for the dilate image
    # dilate zones
    img_finished_hull3 = np.copy(img_finished_hull)
    dilate_image = dilate_image(img_finished_hull3)

    # get the hulls of the dilated zones
    grouped_hulls_dilate, img_hulls_dilate = get_hulls(dilate_image)
    

    """
    image3 = np.copy(image)
    # Get the edges of the polygon
    edges = []
    edges_polygone = []
    for group in grouped_hulls_dilate:
        for i in range(len(group)):
            edge = [[group[i][0][0], group[i][0][1]], [group[(i+1)%len(group)][0][0], group[(i+1)%len(group)][0][1]]]
            edges.append(edge)

        # Print the edges as points and save them in an array

        points = []
        for edge in edges:
            p1 = tuple(edge[0])
            #p2 = tuple(edge[1])
            points.append(p1)
            #points.append(p2)
            cv2.circle(image3, p1, 3, (0, 255, 0), 1)
            #cv2.circle(image3, p2, 3, (0, 255, 0), 3)
        edges_polygone.append(edges)
    """

    dude = [[174.50415,494.59368],[215.21844,478.87939],[207.36129,458.87939],[203.07558,441.02225],[203.07558,418.1651],
    [210.93272,394.59367],[224.50415,373.1651],[241.64701,358.1651],[257.36129,354.59367],[275.93272,356.73653],
    [293.07558,359.59367],[309.50415,377.45082],[322.36129,398.1651],[331.64701,421.73653],[335.21844,437.45082],
    [356.64701,428.52225],[356.1113,428.34367],[356.1113,428.34367],[368.78987,419.59368],[349.50415,384.59367],
    [323.78987,359.59367],[290.93272,343.87939],[267.36129,341.02225],[264.50415,331.02225],[264.50415,321.02225],
    [268.78987,306.02225],[285.93272,286.02225],[295.21844,270.30796],[303.78987,254.59367],[306.64701,213.87939],
    [320,202.36218],[265,202.36218],[286.64701,217.45082],[293.78987,241.02225],[285,257.36218],[270.93272,271.73653],
    [254.50415,266.02225],[250.93272,248.1651],[256.64701,233.1651],[256.64701,221.02225],[245.93272,215.30796],
    [238.78987,216.73653],[233.78987,232.45082],[232.36129,249.59367],[243.07558,257.09367],[242.89701,270.30796],
    [235.93272,279.95082],[222.36129,293.1651],[205.21844,300.6651],[185,297.36218],[170,242.36218],[175,327.36218],
    [185,322.36218],[195,317.36218],[230.75415,301.02225],[235.39701,312.45082],[240.57558,323.52225],
    [243.61129,330.48653],[245.21844,335.12939],[245.03987,344.4151],[229.86129,349.4151],[209.14701,362.09367],
    [192.89701,377.80796],[177.18272,402.27225],[172.36129,413.87939],[169.14701,430.48653],[168.61129,458.52225],
    [168.61129,492.80796]]


    test1 = grouped_hulls_dilate[0]
    array1 = [[float(x), float(y)] for point in test1 for x, y in point]


    

    # Convert the points to a NumPy array of shape (n,1,2)
    points_array = np.array([array1], dtype=np.int32)

    image5 = np.copy(image)
    for point in array1:
    # Draw the polygon on the image
        cv2.polylines(image5, [points_array], True, (0, 0, 255), thickness=2)


    cv2.imshow("image5", image5)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # get trapzoid for each hull
    seidel = seidel.Triangulator(array1)
    triangles = seidel.triangles()
    trapezoids = seidel.trapezoids



    plt.figure()
    points2 = []
    trap = []
    for t in trapezoids:
        verts = t.vertices()

        trap.append(verts)
        plt.gca().add_patch(PolygonPatch(Polygon(verts)))
        plt.gca().autoscale(tight=False)
        points2.append(PolygonPatch(Polygon(verts)))

    plt.show()





    image4 = np.copy(image)
    # Convert the points to a NumPy array of shape (n,1,2)
    point_trap = []
    trap_group = []
    for points_trap in trap:
        point_trap = []
        for x,y in points_trap:
            point_trap.append([float(x), float(y)])
        trap_group.append(point_trap)

    points_array = np.array([trap_group], dtype=np.int32)
    for point in trap_group:
        # Draw the polygon on the image
        # Reshape the array to have shape (1, n, 2)
        pts = np.array([point], np.int32)
        pts = pts.reshape((-1, 1, 2))
        cv2.polylines(image4, [pts], True, (0, 0, 255), thickness=2)

        cv2.imshow("image4", image4)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


    # show the images
    cv2.imshow("image", image)
    cv2.imshow("image with polygone for each working zone filtered first", img_finished_hull_working_zones1)
    cv2.imshow("image with polygone for each working zone", img_finished_hull_working_zones2)
    cv2.imshow("image with poligones dilated", img_hulls_dilate)
    cv2.imshow("dilate image", dilate_image)

    cv2.imwrite("img_hulls_dilate.jpg", img_hulls_dilate)




    cv2.waitKey(0)
    cv2.destroyAllWindows()



