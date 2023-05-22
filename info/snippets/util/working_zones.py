import numpy as np
import matplotlib.pyplot as plt

from scipy.ndimage import rotate, binary_erosion, binary_dilation




def zonareparadaInterior(Img, Imgr, Imgd, k):
    Imgr1 = rotate(Imgr, 90)
    Imgd1 = rotate(Imgd, 90)

    # Zona navegable sin salirse de la chapa
    A1 = binary_erosion(Img, Imgr1, iterations=k)

    # Posiciones del robot para cubrir la chapa con la herramienta
    A2 = binary_erosion(Img, Imgd1, iterations=k)
    A2[np.isinf(A2)] = 0

    # Posiciones del robot para cubrir la chapa sin salirse de la misma.
    A3 = np.logical_and(A1, A2)

    # Zona 
    A4 = binary_dilation(A3, Imgd1, iterations=k)
    
    return A1, A2, A3, A4

def zonareparadaExterior(Img, Imgr, Imgd, k):
    Imgr1 = rotate(Imgr, 90)
    Imgd1 = rotate(Imgd, 90)

    A1 = binary_erosion(~Img, Imgr1, iterations=k)

    A2 = binary_erosion(Img, Imgd1, iterations=k)
    A2[np.isinf(A2)] = 0

    A3 = np.logical_and(A1, A2)

    A4 = binary_dilation(A3, Imgd1, iterations=k)

    return A1, A2, A3, A4


if __name__ == '__main__':

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

    # L_vulcano = 114/2
    # H_vulcano = 90/2
    #
    # L_max = (Lc - offsetdx)/2;
    # H_max = (Hc - offsetdy)/2;

    Lr = L_sherpaXL  # min(L_max, H_max);  # 80; cm
    Hr = H_sherpaXL  # min(L_max, H_max);  # sherpa = 58/2; 50; cm
    # mascara del robot
    Imgr = np.ones((int(2 * Hr + 1), int(2 * Lr + 1)))

    offsetdx = 0  # 2*Hr
    offsetdy = 0  # 0

    # Parametros de la herramienta
    Xd = int((Lr + offsetdx))  # cm
    Yd = int((Hr + offsetdy))  # cm
    # mascara de la herramienta
    Imgd = np.zeros((int(2 * abs(Yd) + 1), int(2 * abs(Xd) + 1)))

    #min = int(abs(Yd) + 1 - Yd)
    #max = int(abs(Xd) + 1 + Xd)
    #Imgd[min, max] = 1
    Imgd[np.abs(Yd) + 1 - Yd, np.abs(Xd) + 1 + Xd] = 1

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

    plt.figure()
    plt.imshow(ImgDisp)
    plt.plot([Xi, Xi], [1, 2 * Yi + 1], 'r')
    plt.plot([1, 2 * Xi + 1], [Yi, Yi], 'r')
    plt.show()

    plt.figure()
    plt

