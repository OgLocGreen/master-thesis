import cv2
import numpy as np

# Bild einlesen
image = cv2.imread('panorama.png', 0)

# Konturen erkennen
edges = cv2.Canny(image, 100, 200)
contours, hierarchy = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Konturen gruppieren
# Hier können Sie Clustering-Algorithmen wie K-Means oder DBSCAN verwenden

# Konturen schließen
for contour in contours:
    # Überprüfen, ob die Kontur geschlossen ist
    if cv2.isContourConvex(contour):
        # Kontur schließen, falls sie offen ist
        epsilon = 0.02 * cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, epsilon, True)
        cv2.drawContours(image, [approx], 0, (255, 255, 255), -1)

# Konturen in Weiß zeichnen
contour_image = np.zeros_like(image)
cv2.drawContours(contour_image, contours, -1, (255, 255, 255), -1)

# Hintergrund entfernen
result = cv2.bitwise_and(image, contour_image)

# Ergebnisbilder speichern
cv2.imwrite('originalbild.jpg', image)
cv2.imwrite('konturen.jpg', contour_image)
cv2.imwrite('ergebnis.jpg', result)

# Ergebnis anzeigen
cv2.imshow('Originalbild', image)
cv2.imshow('Konturen', contour_image)
cv2.imshow('Ergebnis', result)
cv2.waitKey(0)
cv2.destroyAllWindows()
