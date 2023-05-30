import numpy as np
import matplotlib.pyplot as plt



# Funciones auxiliares
def zonareparadaInterior(Img, Imgr, Imgd, k):
    Imgr = np.rot90(Imgr)
    Imgd = np.rot90(Imgd)

    A1 = np.logical_not(np.isinf(Img)) & np.rot90(np.logical_not(np.isinf(Imgr)), k)

    A2 = np.logical_not(np.isinf(Img)) & np.rot90(np.logical_not(np.isinf(Imgd)), k)
    A2[np.isinf(A2)] = 0

    A3 = A1 & A2

    A4 = np.rot90(np.logical_not(np.isinf(A3)), k)

    return A1, A2, A3, A4



def zonareparadaExterior(Img, Imgr, Imgd, k):
    Imgr1 = np.rot90(Imgr)
    Imgd1 = np.rot90(Imgd)

    A1 = np.rot90(np.logical_not(Img), k) & np.rot90(np.logical_not(Imgr), k)

    A2 = np.rot90(Img, k) & np.rot90(np.isinf(Imgd), k)
    A2[np.isinf(A2)] = False

    A3 = np.logical_and(A1, A2)

    A4 = np.rot90(np.logical_or(A3, np.isinf(Imgd)), k)

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

Lr = int(L_sherpaXL)  # min(L_max, H_max);  %80; %cm
Hr = int(H_sherpaXL)  # min(L_max, H_max); % sherpa = 58/2; 50; %cm
# mascara del robot
Imgr = np.ones((2 * Hr + 1, 2 * Lr + 1))

offsetdx = 0  # 2*Hr;
offsetdy = 0  # 0;

# Parametros de la herramienta
Xd = int(Lr + offsetdx)  # cm
Yd = int(Hr + offsetdy)  # cm
# mascara de la herramienta
max_Xd = abs(Xd) + 1
max_Yd = abs(Yd) + 1
Imgd = np.zeros((2 * max_Yd + 1, 2 * max_Xd + 1))
Imgd[max_Yd - Yd, max_Xd + Xd] = 1


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
ImgDisp[(D4 == 1) & ((A4 + B4 + C4) == 0)] = 5
plt.imshow(ImgDisp)

plt.figure(1)
plt.imshow(ImgDisp)
plt.plot([Xi, Xi], [1, 2 * Yi + 1], 'r')
plt.plot([1, 2 * Xi + 1], [Yi, Yi], 'r')

plt.figure(2)
plt.plot([-Lc, Lc, Lc, -Lc, -Lc], [Hc, Hc, -Hc, -Hc, Hc], color=[0.2667, 0.3882, 0.9882], linewidth=1.5)
plt.axis([-350, 350, -200, 200])
plt.axis('square')
plt.axis('equal')
plt.plot([-(Lc - (max(Lr, -Xd) + Xd)), Lc - max(Lr, Xd) + Xd, Lc - max(Lr, Xd) + Xd, -(Lc - (max(Lr, -Xd) + Xd)),
          -(Lc - (max(Lr, -Xd) + Xd))],
         [Hc - max(Hr, Yd) + Yd, Hc - max(Hr, Yd) + Yd, -(Hc - (max(Hr, -Yd) + Yd)), -(Hc - (max(Hr, -Yd) + Yd)),
          Hc - max(Hr, Yd) + Yd],
         color=[0.1098, 0.6627, 0.8745], linewidth=1.5)
plt.plot([-(Lc - (max(Hr, Yd) - Yd)), Lc - max(Hr, -Yd) - Yd, Lc - max(Hr, -Yd) - Yd, -(Lc - (max(Hr, Yd) - Yd)),
          -(Lc - (max(Hr, Yd) - Yd))],
         [Hc - max(Lr, Xd) + Xd, Hc - max(Lr, Xd) + Xd, -(Hc - (max(Lr, -Xd) + Xd)), -(Hc - (max(Lr, -Xd) + Xd)),
          Hc - max(Lr, Xd) + Xd],
         color=[0.2902, 0.7961, 0.5176], linewidth=1.5)
plt.plot([-(Lc - (max(Lr, Xd) - Xd)), Lc - max(Lr, -Xd) - Xd, Lc - max(Lr, -Xd) - Xd, -(Lc - (max(Lr, Xd) - Xd)),
          -(Lc - (max(Lr, Xd) - Xd))],
         [Hc - max(Hr, -Yd) - Yd, Hc - max(Hr, -Yd) - Yd, -(Hc - (max(Hr, Yd) - Yd)), -(Hc - (max(Hr, Yd) - Yd)),
          Hc - max(Hr, -Yd) - Yd],
         color=[0.9373, 0.7255, 0.2078], linewidth=1.5)
plt.plot([-(Lc - (max(Hr, -Yd) + Yd)), Lc - max(Hr, Yd) + Yd, Lc - max(Hr, Yd) + Yd, -(Lc - (max(Hr, -Yd) + Yd)),
          -(Lc - (max(Hr, -Yd) + Yd))],
         [Hc - max(Lr, -Xd) - Xd, Hc - max(Lr, -Xd) - Xd, -(Hc - (max(Lr, Xd) - Xd)), -(Hc - (max(Lr, Xd) - Xd)),
          Hc - max(Lr, -Xd) - Xd],
         color=[0.9765, 0.9804, 0.07843], linewidth=1.5)

plt.show()

