import cv2
import numpy as np

# Laden des Bildes
image = cv2.imread('panorama.png')

# Überprüfen, ob das Bild erfolgreich geladen wurde
if image is None:
    print("Fehler: Das Bild konnte nicht geladen werden.")
    exit()

# Konvertiere das Bild in Graustufen
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Anwenden von Bilddurchschnitt
_, thresh = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY)

# Finde Konturen im Bild
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Erstelle eine leere Maske für das Ergebnis
mask = np.zeros_like(image)

# Definiere eine Flächengrenze, um kleine Konturen zu entfernen (anpassbar)
min_area = 1000

# Erstelle eine leere Liste, um die gruppierten Konturen zu speichern
grouped_contours = []

# Füge den Rand des Bildes als Kontur hinzu
height, width, _ = image.shape
border_contour = np.array([[[0, 0]], [[0, height-1]], [[width-1, height-1]], [[width-1, 0]]], dtype=np.int32)
cv2.drawContours(mask, [border_contour], 0, (255, 255, 255), 2)

# Iteriere über alle gefundenen Konturen
for contour in contours:
    # Berechne den Umfang der Kontur
    perimeter = cv2.arcLength(contour, True)

    # Approximiere die Kontur zu einer geschlossenen Kontur mit weniger Ecken
    epsilon = 0.02 * perimeter
    approx = cv2.approxPolyDP(contour, epsilon, True)

    # Berechne die Fläche der Kontur
    area = cv2.contourArea(contour)

    # Filtere Konturen mit kleiner Fläche heraus (z.B. Schriften)
    if area >= min_area and len(approx) >= 3:
        # Zeichne die Kontur in Weiß auf der Maske
        cv2.drawContours(mask, [contour], 0, (255, 255, 255), -1)

        # Füge die Kontur zur gruppierten Konturenliste hinzu
        grouped_contours.append(contour)

# Speichere das Ergebnisbild
cv2.imwrite("konturen_mit_rand.jpg", mask)

# Schleife über gruppierte Konturen
for i in range(len(grouped_contours)):
    # Berechne das Schwerpunktzentrum der Kontur
    M = cv2.moments(grouped_contours[i])
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])

    # Überprüfen, ob der Schwerpunkt nahe genug am Rand ist
    margin = 10 # anpassbarer Randabstand
    height, width = image.shape[:2]
    if cX < margin:
        # Zeichne Linie zum linken Rand
        cv2.line(mask, (cX, cY), (0, cY), (0, 0, 255), 2)
    elif cX > width - margin:
        # Zeichne Linie zum rechten Rand
        cv2.line(mask, (cX, cY), (width, cY), (0, 0, 255), 2)
    if cY < margin:
        # Zeichne Linie zum oberen Rand
        cv2.line(mask, (cX, cY), (cX, 0), (0, 0, 255), 2)
    elif cY > height - margin:
        # Zeichne Linie zum unteren Rand
        cv2.line(mask, (cX, cY), (cX, height), (0, 0, 255), 2)


# Speichere das Ergebnis als Bild
cv2.imwrite('kontur_mit_rand.png', mask)