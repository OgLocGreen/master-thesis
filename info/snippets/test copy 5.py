import cv2
import numpy as np

# Lade das Bild und konvertiere es in Graustufen
img = cv2.imread('circles.png')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Wende eine Canny-Kantenerkennung an, um die Kontur der Fläche zu finden
canny = cv2.Canny(gray, 100, 200)

# Finde die Kontur der Fläche
contours, hierarchy = cv2.findContours(canny, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Erstelle ein Rechteck mit der gleichen Breite wie das Bild
width = img.shape[1]
rect_width = 25

# Gehe jede Kontur durch und decke sie mit Rechtecken ab
for contour in contours:
    x, y, w, h = cv2.boundingRect(contour)
    for i in range(x, x + w, rect_width):
        cv2.rectangle(img, (i, y), (i + rect_width, y + h), (0, 0, 255), 2)

# Zeige das Bild mit den Rechtecken an
cv2.imshow('Bild mit Rechtecken', img)
cv2.waitKey(0)
cv2.destroyAllWindows()