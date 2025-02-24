# Algoritmia básica - Práctica 2
# Nicolás de Rivas (843740)
# Cristina Embid (842102)
import numpy as np
import math


# Calcula la energía de un píxel
# @param brillo matriz 2D que cada componente representa el brillo de ese pixel
# @param fil índice válido dentro de la imagen que representa la fila
# @param col índice válido dentro de la imagen que representa la columna
# @return devuelve valor numérico que representa la energía de un píxel
def energiaPixel(brillo, fil, col):
    a = brillo[fil - 1][col - 1]
    d = brillo[fil][col - 1]
    g = brillo[fil + 1][col - 1]
    b = brillo[fil - 1][col]
    h = brillo[fil + 1][col]
    c = brillo[fil - 1][col + 1]
    f = brillo[fil][col + 1]
    i = brillo[fil + 1][col + 1]
    energiax = a + 2 * d + g - c - 2 * f - i
    energiay = a + 2 * b + c - g - 2 * h - i
    return math.sqrt(energiax**2 + energiay**2)


# Calcula la energía de cada pixel en la imagen
# @param img matriz 3D que representa la imagen (alto x ancho x canales de color)
# @return matriz con los valores de la energía para cada pixel en la imagen original
def calcularEnergia(img):
    # Nueva matriz con un borde adicional
    formaBrillo = (img.shape[0] + 2, img.shape[1] + 2)
    brillos = np.zeros(formaBrillo)
    for i in range(img.shape[0]):
        for j in range(
            img.shape[1]
        ):  # Calcula el brillo de cada pixel (suma de la componente roja, azul y verde)
            brillos[i + 1][j + 1] = np.int32(img[i][j].sum())
    energias = np.zeros((img.shape[0], img.shape[1]))
    for i in range(1, formaBrillo[0] - 1):
        for j in range(1, formaBrillo[1] - 1):
            energias[i - 1, j - 1] = energiaPixel(
                brillos, i, j
            )  # Se calcula la energía del pixel correspondiente
    return energias


# Reconstruye la costura de menor energía desde la última fila hasta la primera
# @param costuras matriz n x m donde cada componente contiene una tupla con la energía acumulada y el pixel precedente
# @param costuramin índice válido dentro del rango de la matriz
# @return lista que representa la costura de menor energía
def reconstruirCostura(costuras, costuramin):
    costura = [
        (len(costuras) - 1, costuramin)
    ]  # Inicializa la costura con el último píxel de menor energía
    (i, j) = costuras[len(costuras) - 1][costuramin][1]  # Obtiene el pixel precedente
    while costura[-1] != (i, j):  # Se reconstruye hasta llegar a la primera fila
        costura = costura + [(i, j)]
        (i, j) = costuras[i][j][1]  # Se obtiene el siguiente píxel
    return costura


# Encuentra la costura con menor energía en la imagen
# @param energia matriz 2D donde cada elemento representa la energía de un píxel
# @return una lista que representa la costura de menor energía desde la primera hasta la última fila
def minimaCostura(energia):
    n = energia.shape[0]  # Número de filas
    m = energia.shape[1]  # Número de columnas
    # Matriz de tamaño n x m donde cada celda contiene una tupla [energía acumulada, pixel precedente]
    costuras = [[(0, (0, 0)) for j in range(m)] for i in range(n)]
    for i in range(n):
        for j in range(m):
            if i == 0:  # Primera fila toma la energía original
                costuras[i][j] = (energia[i][j], (i, j))
            elif j == 0 and j == m - 1:
                min = costuras[i - 1][j][0]
                precedente = (i - 1, j)
            elif j == 0:
                minind = np.argmin([costuras[i - 1][j][0], costuras[i - 1][j + 1][0]])
                min = [costuras[i - 1][j], costuras[i - 1][j + 1]][minind]
                precedente = [(i - 1, j), (i - 1, j + 1)][minind]
            elif j == m - 1:
                minind = np.argmin([costuras[i - 1][j][0], costuras[i - 1][j - 1][0]])
                min = [costuras[i - 1][j], costuras[i - 1][j - 1]][minind]
                precedente = [(i - 1, j), (i - 1, j - 1)][minind]
            else:
                minind = np.argmin(
                    [
                        costuras[i - 1][j][0],
                        costuras[i - 1][j - 1][0],
                        costuras[i - 1][j + 1][0],
                    ]
                )
                min = [
                    costuras[i - 1][j],
                    costuras[i - 1][j - 1],
                    costuras[i - 1][j + 1],
                ][minind]
                precedente = [(i - 1, j), (i - 1, j - 1), (i - 1, j + 1)][minind]
            if i != 0:
                costuras[i][j] = (
                    min[0] + energia[i][j],
                    precedente,
                )  # Actualiza energía acumulada
    # Encuentra la columna de la última fila con menor energía acumulada
    costuramin = np.argmin([costuras[n - 1][k][0] for k in range(m)])
    return reconstruirCostura(costuras, costuramin)


# Calcula la energía de la imagen y luego encuentra la costura óptima
# @param img matriz 3D que representa la imagen (alto x ancho x canales de color)
# @return devuelve la costura de menor energía como una lista de tuplas
def encontrarCostura(img):
    energias = calcularEnergia(img)  # Calcula la matriz de energía
    return minimaCostura(energias)


# Elimina una costura de la imagen
# @param costura lista de tuplas que representa la costura a eliminar
# @param img matriz 3D que representa la imagen (alto x ancho x canales de color)
# @return imagen con la costura eliminada
def quitarCostura(costura, img):
    for e in costura:
        img[e[0], :-1] = np.append(img[e[0], : e[1]], img[e[0], e[1] + 1 :], axis=0)
        # img[e[0], e[1]] = [255,0,0]
    return img[:, :-1]
    # return img
