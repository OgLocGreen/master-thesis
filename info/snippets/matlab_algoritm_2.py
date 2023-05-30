import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage import rotate
from scipy.ndimage.morphology import binary_dilation
from scipy.ndimage import binary_erosion

import cv2

def zonareparadaInterior(Img, Imgr, Imgd, k):
    Imgr1 = rotate(Imgr, k * 90)
    Imgd1 = rotate(Imgd, k * 90)

    # Zona navegable sin salirse de la chapa
    A1 = binary_erosion(Img, rotate(Imgr, k*90))

    # Posiciones del robot para cubrir la chapa con la herramienta
    A2 = binary_erosion(Img, rotate(Imgd, k*90))
    A2[np.isinf(A2)] = 0

    # Posiciones del robot para cubrir la chapa sin salirse de la misma.
    A3 = np.logical_and(A1, A2)

    # Zona

    Imgd_rotated = np.rot90(Imgd, k)
    A4 = binary_dilation(A3, structure=Imgd_rotated)


    return A1, A2, A3, A4


def zonareparadaExterior(Img, Imgr, Imgd, k):
    Imgr1 = rotate(Imgr, k * 90)
    Imgd1 = rotate(Imgd, k * 90)

    A1 = np.logical_and(np.logical_not(Img), rotate(Imgr, k))

    A2 = np.logical_and(Img, rotate(Imgd, k))
    A2[np.isinf(A2)] = 0

    A3 = np.logical_and(A1, A2)

    A4 = np.logical_or(rotate(A3, -k), rotate(Imgd, k))

    return A1, A2, A3, A4

# Parametros de la chapa
Lc = 300  # cm
Hc = 150  # cm

# para generar las imagenes
Xi = Lc + 200  # cm
Yi = Hc + 200  # cm
Img = np.zeros((2 * Yi + 1, 2 * Xi + 1))

Img[Yi - Hc:Yi + Hc + 1, Xi - Lc:Xi + Lc + 1] = 1

plt.imshow(Img)

# Parametros del robot (Dimensiones en cm)
L_sherpaXL = 44 / 2
H_sherpaXL = 58 / 2

Lr = int(L_sherpaXL)  # min(L_max, H_max)  # 80  # cm
Hr = int(H_sherpaXL)  # min(L_max, H_max)  # sherpa = 58/2; 50  # cm
# mascara del robot
Imgr = np.ones((2 * Hr + 1, 2 * Lr + 1))

offsetdx = 0  # 2 * Hr
offsetdy = 0  # 0

# Parametros de la herramienta
Xd = Lr + offsetdx  # cm
Yd = Hr + offsetdy  # cm
# mascara de la herramienta
"""
max_Xd = abs(Xd) + 1
max_Yd = abs(Yd) + 1
Imgd = np.zeros((2 * max_Yd + 1, 2 * max_Xd + 1))
Imgd[max_Yd - Yd, max_Xd + Xd] = 1
"""

Imgd = np.zeros((2 * abs(Yd) + 1, 2 * abs(Xd) + 1))
Imgd[abs(Yd)-Yd , abs(Xd)+Xd ] = 1

# Zona navegable con ejes paralelos
A1, A2, A3, A4 = zonareparadaInterior(Img, Imgr, Imgd, 0)
ImgDisp = Img.copy()
ImgDisp[A4 == 1] = 2
plt.imshow(ImgDisp)

# Zona cubierta cuando el robot gira 90 grados
B1, B2, B3, B4 = zonareparadaInterior(Img, Imgr, Imgd, 1)
ImgDisp[(B4 == 1) & (A4 == 0)] = 3
plt.imshow(ImgDisp)


# Rotacion de 180 grados
C1, C2, C3, C4 = zonareparadaInterior(Img, Imgr, Imgd, 2)
ImgDisp[(C4 == 1) & ((A4 + B4) == 0)] = 4


plt.imshow(ImgDisp)


# Rotacion de 270 grados
D1, D2, D3, D4 = zonareparadaInterior(Img, Imgr, Imgd, 3)
ImgDisp[(D4 ==1) & ((A4 + B4 + C4) == 0)] = 5

plt.imshow(ImgDisp)


plt.figure(1)
plt.imshow(ImgDisp)
plt.plot([Xi, Xi], [1, 2 * Yi + 1], 'r')
plt.plot([1, 2 * Xi + 1], [Yi, Yi], 'r')

plt.figure(2)
plt.plot(Lc * np.array([-1, 1, 1, -1, -1]), Hc * np.array([1, 1, -1, -1, 1]), 'b-', linewidth=1.5)
plt.axis([-350, 350, -200, 200])
plt.axis('square')
plt.axis('equal')
# 0 grados
plt.plot(
    [-(Lc - (max(Lr, -Xd) + Xd)), Lc - max(Lr, Xd) + Xd, Lc - max(Lr, Xd) + Xd, -(Lc - (max(Lr, -Xd) + Xd)),
     -(Lc - (max(Lr, -Xd) + Xd))],
    [Hc - max(Hr, Yd) + Yd, Hc - max(Hr, Yd) + Yd, -(Hc - (max(Hr, -Yd) + Yd)), -(Hc - (max(Hr, -Yd) + Yd)),
     Hc - max(Hr, Yd) + Yd],
    'g-', linewidth=1.5)
# 90 grados
plt.plot(
    [-(Lc - (max(Hr, Yd) - Yd)), Lc - max(Hr, -Yd) - Yd, Lc - max(Hr, -Yd) - Yd, -(Lc - (max(Hr, Yd) - Yd)),
     -(Lc - (max(Hr, Yd) - Yd))],
    [Hc - max(Lr, Xd) + Xd, Hc - max(Lr, Xd) + Xd, -(Hc - (max(Lr, -Xd) + Xd)), -(Hc - (max(Lr, -Xd) + Xd)),
     Hc - max(Lr, Xd) + Xd],
    'r-', linewidth=1.5)
# 180 grados
plt.plot(
    [-(Lc - (max(Lr, Xd) - Xd)), Lc - max(Lr, -Xd) - Xd, Lc - max(Lr, -Xd) - Xd, -(Lc - (max(Lr, Xd) - Xd)),
     -(Lc - (max(Lr, Xd) - Xd))],
    [Hc - max(Hr, -Yd) - Yd, Hc - max(Hr, -Yd) - Yd, -(Hc - (max(Hr, Yd) - Yd)), -(Hc - (max(Hr, Yd) - Yd)),
     Hc - max(Hr, -Yd) - Yd],
    'c-', linewidth=1.5)
# 270 grados
plt.plot(
    [-(Lc - (max(Hr, -Yd) + Yd)), Lc - max(Hr, Yd) + Yd, Lc - max(Hr, Yd) + Yd, -(Lc - (max(Hr, -Yd) + Yd)),
     -(Lc - (max(Hr, -Yd) + Yd))],
    [Hc - max(Lr, -Xd) - Xd, Hc - max(Lr, -Xd) - Xd, -(Hc - (max(Lr, Xd) - Xd)), -(Hc - (max(Lr, Xd) - Xd)),
     Hc - max(Lr, -Xd) - Xd],
    'm-', linewidth=1.5)

plt.show()