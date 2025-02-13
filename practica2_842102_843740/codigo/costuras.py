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
    energias = np.zeros(img.shape) # Esto no es image.shape, solo quiero un valor, no RGB
    for i in range(1, imgGrande.shape[0] - 1):
        for j in range(1, imgGrande.shape[1] - 1):
            energias[i-1, j-1] = energiaPixel(imgGrande, i, j)
    return energias

def c(energias, i, j):
    if i == 0:
        return (energias[i, j], [(i, j)])
    if j == 0:
        dos = c(energias, i-1, j)
        tres = c(energias, i-1, j+1)
        pixel = np.argmin([dos[0], tres[0]])
        print([dos[0], tres[0]], pixel)
        print("2:", dos)
        print("3:", tres)
        [dos, tres][pixel][1].append((i, j))
        return (energias[i, j] + [dos, tres][pixel][0], [dos, tres][pixel][1])
    if j == energias.shape[1] - 1:
        uno = c(energias, i-1, j-1)
        dos = c(energias, i-1, j)
        pixel = np.argmin([uno[0], dos[0]])
        [uno, dos][pixel][1].append((i, j))
        return (energias[i, j] + [uno, dos][pixel][0], [uno, dos][pixel][1])
    uno = c(energias, i-1, j-1)
    dos = c(energias, i-1, j)
    tres = c(energias, i-1, j+1)
    pixel = np.argmin([uno[0], dos[0], tres[0]])
    [uno, dos, tres][pixel][1].append((i, j))
    return (energias[i, j] + [uno, dos, tres][pixel][0], [uno, dos, tres][pixel][1])

def encontrarCostura(img):
    energias = calcularEnergia(img)
    (valor, costura) = c(energias, img.shape[0]-1, 0)
    for j in range(1, img.shape[1]):
        print("Costura: ", valor)
        oldValor = valor
        (valor, costura) = c(energias, img.shape[0]-1, j)
        if valor < oldValor:
            costuraFinal = costura
    return costuraFinal

def quitarCostura(costura, img):
    for e in costura:
        img[e[0], :-1] = np.append(img[e[0], :e[1]], img[e[0], e[1]+1:])
    return img[:, :-1]
