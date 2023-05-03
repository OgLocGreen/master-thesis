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
rect_width = 20

# Gehe jede Kontur durch und decke sie mit Rechtecken ab
for contour in contours:
    x, y, w, h = cv2.boundingRect(contour)
    num_rects = int(np.ceil(w / rect_width)) # Berechne die Anzahl der Rechtecke, die benötigt werden
    for i in range(num_rects):
        rect_x = x + i * rect_width
        if i == num_rects - 1: # Das letzte Rechteck darf sich überschneiden
            rect_width_last = w - i * rect_width
            cv2.rectangle(img, (rect_x, y), (rect_x + rect_width_last, y + h), (0, 0, 255), 2)
        else:
            cv2.rectangle(img, (rect_x, y), (rect_x + rect_width, y + h), (0, 0, 255), 2)

# Zeige das Bild mit den Rechtecken an
cv2.imshow('Bild mit Rechtecken', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
