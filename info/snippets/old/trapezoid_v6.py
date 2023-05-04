import cv2
import numpy as np
import matplotlib.pyplot as plt


def split_polygon_into_trapezoids(polygon):
    trapezoids = []
    while len(polygon) > 2:
        # Step 1: Find two adjacent vertices that are not part of the same edge
        i, j, k = find_adjacent_vertices(polygon)

        # Step 2: Construct a line between the two vertices
        line = construct_line(polygon[i], polygon[j])

        # Step 3: Determine which vertices are above and below the line
        above = []
        below = []
        for l in range(len(polygon)):
            if l != i and l != j:
                if np.cross(line[1]-line[0], polygon[l]-line[0]) > 0:
                    below.append(l)
                else:
                    above.append(l)
        
        above = sorted(above, key=lambda p: np.arctan2(p[1]-line[0][1], p[0]-line[0][0]))
        below = sorted(below, key=lambda p: np.arctan2(p[1]-line[0][1], p[0]-line[0][0]))

        # Step 4: Create trapezoids by connecting vertices above and below the line
        for m in range(len(below)-1):
            trapezoids.append([polygon[below[m]], polygon[below[m+1]], polygon[above[0]], polygon[above[-1]]])
        for n in range(len(above)-1):
            trapezoids.append([polygon[above[n]], polygon[above[n+1]], polygon[below[-1]], polygon[below[0]]])

        # Step 5: Split the polygon into two parts
        polygon = [polygon[j]] + polygon[j+1:i+1] + [polygon[i]] + below[::-1] + above[::-1]

    # Add the final trapezoid
    trapezoids.append(polygon)

    return trapezoids


def find_adjacent_vertices(polygon):
    for i in range(len(polygon)):
        j = (i + 1) % len(polygon)
        k = (i + 2) % len(polygon)
        if not collinear(polygon[i], polygon[j], polygon[k]):
            return i, j, k


def construct_line(p1, p2):
    return p1, p2


def collinear(p1, p2, p3):
    return np.abs(np.cross(p2-p1, p3-p1)) < 1e-9


# Load image
img = cv2.imread("your_image.jpg")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Find external contour
contours, hierarchy = cv2.findContours(gray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Extract polygon from contour
polygon = contours[0].squeeze()

# Split polygon into trapezoids
trapezoids = split_polygon_into_trapezoids(polygon)

# Plot the results
fig, ax = plt.subplots()
for trapezoid in trapezoids:
    ax.fill(trapezoid[:,0], trapezoid[:,1], alpha=0.5)
ax.plot(polygon[:,0], polygon[:,1], 'k--')
plt.show()
