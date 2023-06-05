import numpy as np
import matplotlib.pyplot as plt
import cv2
from scipy.ndimage import rotate
from scipy.ndimage.morphology import binary_dilation
from scipy.ndimage import binary_erosion


def zonareparadaInterior(Img, Imgr, Imgd, k):
    Imgr1 = rotate(Imgr, k * 90)
    Imgd1 = rotate(Imgd, k * 90)
    if len(Img.shape) == 3:
        gray_image = cv2.cvtColor(Img, cv2.COLOR_BGR2GRAY)
        _, binary_image = cv2.threshold(gray_image, 127, 255, cv2.THRESH_BINARY)
    else:
        binary_image = Img
    # Zona navegable sin salirse de la chapa
    A1 = binary_erosion(binary_image, rotate(Imgr, k*90))

    # Posiciones del robot para cubrir la chapa con la herramienta
    A2 = binary_erosion(binary_image, rotate(Imgd, k*90))
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

    gray_image = cv2.cvtColor(Img, cv2.COLOR_BGR2GRAY)
    _, binary_image = cv2.threshold(gray_image, 127, 255, cv2.THRESH_BINARY)

    A1 = np.logical_and(np.logical_not(binary_image), rotate(Imgr, k))

    A2 = np.logical_and(binary_image, rotate(Imgd, k))
    A2[np.isinf(A2)] = 0

    A3 = np.logical_and(A1, A2)

    A4 = np.logical_or(rotate(A3, -k), rotate(Imgd, k))

    return A1, A2, A3, A4

def make_working_zones(\
        image = None, Hc = int(150), Lc = int(300), Yd = 40, Xd = 60, H_sherpaXL = 58 / 2, L_sherpaXL = 44 / 2):
    
        # Needed variables
    # Hc = Hälfte der Breite des Blechs entspricht der Höhe des Bildes
    # Lc = Hälfte der Länge des Blechs entspricht der Breite des Bildes
    # Yd = Abstand y der Kamera vom Mittelpunkt des Robots
    # Xd = Abstand x der Kamera vom Mittelpunkt des Robots
    # hr = älfte der Breite des Robots
    # Lr = Hälfte der Länge zwischen den Rädern des Robots
    # Parametros de la chapa
    """
    Lc = 300  # cm
    Hc = 150  # cm

    # para generar las imagenes
    Img = np.zeros((2 * Yi + 1, 2 * Xi + 1))
    Img[Yi - Hc:Yi + Hc + 1, Xi - Lc:Xi + Lc + 1] = 1
    """

    # normale uso
    if image is None and __name__ != '__main__':
        print("Error: image is None")
    elif __name__ != '__main__':
        Img = image
        Hc = int(Img.shape[0]/2)
        Lc = int(Img.shape[1]/2)
        Xi = Lc + 200  # cm
        Yi = Hc + 200  # cm
    else:
        Xi = Lc + 200  # cm
        Yi = Hc + 200  # cm
        Img = np.zeros((2 * Yi + 1, 2 * Xi + 1))
        Img[Yi - Hc:Yi + Hc + 1, Xi - Lc:Xi + Lc + 1] = 1




    plt.imshow(Img)

    # Parametros del robot (Dimensiones en cm)
    """
    L_sherpaXL = 44 / 2
    H_sherpaXL = 58 / 2
    """
    Lr = int(L_sherpaXL)  # min(L_max, H_max)  # 80  # cm
    Hr = int(H_sherpaXL)  # min(L_max, H_max)  # sherpa = 58/2; 50  # cm

    # mascara del robot
    Imgr = np.ones((2 * Hr + 1, 2 * Lr + 1))
    #Imgr = np.ones_like(Img)

    offsetdx = 0  # 2 * Hr
    offsetdy = 0  # 0

    # Parametros de la herramienta
    Xd = Lr + offsetdx  # cm
    Yd = Hr + offsetdy  # cm

    # mascara de la herramienta
    
    Imgd = np.zeros((2 * abs(Yd) + 1, 2 * abs(Xd) + 1))
    print("Imgd", Imgd.shape)
    print("Imgr", Imgr.shape)
    print("Img",Img.shape)
    #Imgd = np.zeros_like(Img)
    #Imgd[abs(Yd)-Yd , abs(Xd)+Xd ] = 1  #FIXME: Understand what does this here?

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
    plt.show()
    
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
    x = np.array([-(Lc - (max(Lr, -Xd) + Xd)), Lc - max(Lr, Xd) + Xd, Lc - max(Lr, Xd) + Xd, -(Lc - (max(Lr, -Xd) + Xd)), -(Lc - (max(Lr, -Xd) + Xd))])
    y = np.array([Hc - max(Hr, Yd) + Yd, Hc - max(Hr, Yd) + Yd, -(Hc - (max(Hr, -Yd) + Yd)), -(Hc - (max(Hr, -Yd) + Yd)), Hc - max(Hr, Yd) + Yd])
    x1, y1 = x[0], y[0]
    x2, y2 = x[2], y[2]
    z0 = [(x1,y1),(x2,y2)]
    plt.plot(x, y, 'g-', linewidth=1.5)

    # 90 grados
    x = np.array([-(Lc - (max(Hr, Yd) - Yd)), Lc - max(Hr, -Yd) - Yd, Lc - max(Hr, -Yd) - Yd, -(Lc - (max(Hr, Yd) - Yd)), -(Lc - (max(Hr, Yd) - Yd))])
    y = np.array([Hc - max(Lr, Xd) + Xd, Hc - max(Lr, Xd) + Xd, -(Hc - (max(Lr, -Xd) + Xd)), -(Hc - (max(Lr, -Xd) + Xd)), Hc - max(Lr, Xd) + Xd])
    x1, y1 = x[0], y[0]
    x2, y2 = x[2], y[2]
    z90 = [(x1,y1),(x2,y2)]
    plt.plot(x, y, 'r-', linewidth=1.5)

    # 180 grados
    x = np.array([-(Lc - (max(Lr, Xd) - Xd)), Lc - max(Lr, -Xd) - Xd, Lc - max(Lr, -Xd) - Xd, -(Lc - (max(Lr, Xd) - Xd)), -(Lc - (max(Lr, Xd) - Xd))])
    y = np.array([Hc - max(Hr, -Yd) - Yd, Hc - max(Hr, -Yd) - Yd, -(Hc - (max(Hr, Yd) - Yd)), -(Hc - (max(Hr, Yd) - Yd)), Hc - max(Hr, -Yd) - Yd])
    x1, y1 = x[0], y[0]
    x2, y2 = x[2], y[2]
    z180 = [(x1,y1),(x2,y2)]
    plt.plot(x, y, 'c-', linewidth=1.5)

    # 270 grados
    x = np.array([-(Lc - (max(Hr, -Yd) + Yd)), Lc - max(Hr, Yd) + Yd, Lc - max(Hr, Yd) + Yd, -(Lc - (max(Hr, -Yd) + Yd)), -(Lc - (max(Hr, -Yd) + Yd))])
    y = np.array([Hc - max(Lr, -Xd) - Xd, Hc - max(Lr, -Xd) - Xd, -(Hc - (max(Lr, Xd) - Xd)), -(Hc - (max(Lr, Xd) - Xd)), Hc - max(Lr, -Xd) - Xd])
    x1, y1 = x[0], y[0]
    x2, y2 = x[2], y[2]
    z270 = [(x1,y1),(x2,y2)]
    plt.plot(x, y, 'm-', linewidth=1.5)

    plt.show()
    return z0, z90, z180, z270

if __name__ == '__main__':
    # Test the code
    z = make_working_zones()