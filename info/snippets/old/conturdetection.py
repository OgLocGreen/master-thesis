import cv2
import numpy as np

# Laden des Bildes
image = cv2.imread('panorama.png')

# Überprüfen, ob das Bild erfolgreich geladen wurde
if image is None:
    print("Fehler: Das Bild konnte nicht geladen werden.")
    exit()

# Konvertieren in Graustufen
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Anwenden einer Schwellenwertbildung
_, thresholded = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)

# Konturen finden
contours, hierarchy = cv2.findContours(thresholded, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

# Einen leeren weißen Hintergrund erstellen
result = np.full_like(image, (255, 255, 255), dtype=np.uint8)

# Einen leeren schwarzen Hintergrund erstellen
#result =  np.zeros_like(image)

# Konturen zeichnen, die nahezu geschlossen sind

#for contour in contours:
#    epsilon = 0.1 * cv2.arcLength(contour, True)
#    approx = cv2.approxPolyDP(contour, epsilon, True)
#    if cv2.isContourConvex(approx):
#        cv2.drawContours(result, [contour], -1, (1, 1, 1), cv2.FILLED)

# Nur geschlossene Konturen in Weiß zeichnen
for contour in contours:
    if cv2.isContourConvex(contour):
        cv2.drawContours(result, [contour], -1, (1, 1, 1), cv2.FILLED)


# Ergebnis anzeigen
cv2.imshow('Nearly Closed Contours in Black', result)

# Ergebnis speichern
cv2.imwrite('panorama_contours.png', result)

cv2.waitKey(0)
cv2.destroyAllWindows()