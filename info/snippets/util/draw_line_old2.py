import cv2
import numpy as np



from PIL import Image, ImageDraw

def draw_stripes(image, angle, stripe_width=5):

    # Erstellen Sie ein Draw-Objekt
    draw = ImageDraw.Draw(image)

    # Bestimmen Sie die Dimensionen des Bildes
    width, height = image.size

    # Bestimmen Sie den Startpunkt und die Richtung basierend auf dem Winkel
    if 0 <= angle < 90:
        start = (width, height)
        end = (0, 0)
    elif 90 <= angle < 180:
        start = (0, height)
        end = (width, 0)
    else:
        raise ValueError("Angle must be between 0 and 180 degrees")

    # Zeichnen Sie die Streifen
    for i in range(0, max(width, height), stripe_width):
        draw.line([start, end], fill='black', width=stripe_width)
        if 0 <= angle < 90:
            start = (start[0] - stripe_width, start[1])
            end = (end[0] + stripe_width, end[1])
        else:
            start = (start[0] + stripe_width, start[1])
            end = (end[0] - stripe_width, end[1])

    # Zeigen Sie das Bild an
    image.show()


# Erstellen Sie ein leeres weißes Bild
image = Image.new('RGB', (500, 500), 'white')

# Verwenden Sie die Funktion
draw_stripes(image, 45)
