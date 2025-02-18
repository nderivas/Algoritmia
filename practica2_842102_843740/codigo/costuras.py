import numpy as np
import math

def energiaPixel(img, fil, col):
    a = np.int32(img[fil-1][col-1].sum())
    d = np.int32(img[fil][col-1].sum())
    g = np.int32(img[fil+1][col-1].sum())
    b = np.int32(img[fil-1][col].sum())
    h = np.int32(img[fil+1][col].sum())
    c = np.int32(img[fil-1][col+1].sum())
    f = np.int32(img[fil][col+1].sum())
    i = np.int32(img[fil+1][col+1].sum())
    energiax = a + 2*d + g - c - 2*f - i
    energiay = a + 2*b + c - g - 2*h - i
    return math.sqrt(energiax**2 + energiay**2)

def calcularEnergia(img):
    formaGrande = (img.shape[0] + 2, img.shape[1] + 2, img.shape[2])
    imgGrande = np.zeros(formaGrande)
    imgGrande[1:-1, 1:-1, :] = img
    energias = np.zeros((img.shape[0], img.shape[1])) # Esto no es image.shape, solo quiero un valor, no RGB
    for i in range(1, imgGrande.shape[0] - 1):
        for j in range(1, imgGrande.shape[1] - 1):
            energias[i-1, j-1] = energiaPixel(imgGrande, i, j)
    return energias

def minimaCostura(energia):
    n = energia.shape[0]
    m = energia.shape[1]
    costuras = [[(0, []) for j in range(m)] for i in range(n)]
    for i in range(n):
        for j in range(m):
            if i == 0:
                costuras[i][j] = (energia[i][j], [(i, j)])
            else:
                valor1 = np.inf if j == 0 else costuras[i-1][j-1][0]
                valor2 = costuras[i-1][j][0]
                valor3 = np.inf if j == m - 1 else costuras[i-1][j+1][0]
                minind = np.argmin([valor1, valor2, valor3])
                min = [0 if j == 0 else costuras[i-1][j-1],
                       costuras[i-1][j],
                       0 if j == m - 1 else costuras[i-1][j+1]][minind]
                costuras[i][j] = (min[0] + energia[i][j], min[1] + [(i, j)])
    costuramin = np.argmin([costuras[n-1][k][0] for k in range(m)])
    return costuras[n-1][costuramin][1]

def encontrarCostura(img):
    energias = calcularEnergia(img)
    print("Termina la energia")
    return minimaCostura(energias)

def quitarCostura(costura, img):
    for e in costura:
        img[e[0], :-1] = np.append(img[e[0], :e[1]], img[e[0], e[1]+1:], axis=0)
    return img[:, :-1]
