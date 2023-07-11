import cv2
import numpy as np
import os

aktuelles_verzeichnis = os.getcwd()
print("Aktuelles Verzeichnis:", aktuelles_verzeichnis)

# Load shape
image = cv2.imread("./snippets/panorama_hulls.png", cv2.IMREAD_GRAYSCALE)



# Binärbild erstellen
_, binary = cv2.threshold(image, 225, 255, cv2.THRESH_BINARY_INV)

# Konturen finden
contours, _ = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# Maske erstellen
mask = np.zeros_like(image)

# Konturen in der Maske füllen
for contour in contours:
    cv2.drawContours(mask, [contour], 0, (255, 255, 255), -1)

# Maske auf das Bild anwenden und mit Rot füllen
red_image = np.zeros_like(image)
red_image[:, :, :] = [0, 0, 255]  # Rot
filled_image = cv2.bitwise_and(red_image, mask)

# Bild anzeigen
cv2.imshow('Filled Contours', filled_image)
cv2.waitKey(0)
cv2.destroyAllWindows()