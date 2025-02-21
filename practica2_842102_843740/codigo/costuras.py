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
    energias = np.zeros((img.shape[0], img.shape[1]))
    for i in range(1, imgGrande.shape[0] - 1):
        for j in range(1, imgGrande.shape[1] - 1):
            energias[i-1, j-1] = energiaPixel(imgGrande, i, j)
    return energias

def reconstruirCostura(costuras, costuramin):
    costura = [(len(costuras)-1, costuramin)]
    (i, j) = costuras[len(costuras)-1][costuramin][1]
    while costura[-1] != (i, j):
        costura = costura + [(i,j)]
        (i, j) = costuras[i][j][1]
    return costura

def minimaCostura(energia):
    n = energia.shape[0]
    m = energia.shape[1]
    costuras = [[(0, (0, 0)) for j in range(m)] for i in range(n)]
    for i in range(n):
        for j in range(m):
            if i == 0:
                costuras[i][j] = (energia[i][j], (i, j))
            elif j == 0 and j == m-1:
                min = costuras[i-1][j][0]
                precedente = (i-1, j)
            elif j == 0:
                minind = np.argmin([costuras[i-1][j][0], costuras[i-1][j+1][0]])
                min = [costuras[i-1][j], costuras[i-1][j+1]][minind]
                precedente = [(i-1, j), (i-1, j+1)][minind]
            elif j == m - 1:
                minind = np.argmin([costuras[i-1][j][0], costuras[i-1][j-1][0]])
                min = [costuras[i-1][j], costuras[i-1][j-1]][minind]
                precedente = [(i-1, j), (i-1, j-1)][minind]
            else:
                minind = np.argmin([costuras[i-1][j][0], costuras[i-1][j-1][0], costuras[i-1][j+1][0]])
                min = [costuras[i-1][j], costuras[i-1][j-1], costuras[i-1][j+1]][minind]
                precedente = [(i-1, j), (i-1, j-1), (i-1, j+1)][minind]
            if i != 0:
                costuras[i][j] = (min[0] + energia[i][j], precedente)
    costuramin = np.argmin([costuras[n-1][k][0] for k in range(m)])
    return reconstruirCostura(costuras, costuramin)

def encontrarCostura(img):
    energias = calcularEnergia(img)
    print("Termina la energia")
    return minimaCostura(energias)

def quitarCostura(costura, img):
    for e in costura:
        img[e[0], :-1] = np.append(img[e[0], :e[1]], img[e[0], e[1]+1:], axis=0)
        # img[e[0], e[1]] = [255,0,0]
    return img[:, :-1]
    # return img
