# Algoritmia básica - Práctica 2
# Nicolás de Rivas (843740)
# Cristina Embid (842102)
import numpy as np
import math
from timer import timer
import imageio as iio


class Costurero:
    # Inicializa el objeto Costurero cargando la imagen, calculando brillos, energías y la matriz de costuras
    @timer
    def __init__(self, path):
        self.primera = True
        self.img = iio.imread(path)  # Leer la imagen
        # Inicialización de brillos con bordes adicionales
        formaBrillo = (self.img.shape[0] + 2, self.img.shape[1] + 2)
        self.brillos = np.zeros(formaBrillo)
        # Calcula el brillo de cada pixel (suma de la componente roja, azul y verde)
        for i in range(self.img.shape[0]):
            for j in range(self.img.shape[1]):
                self.brillos[i + 1][j + 1] = np.int32(self.img[i][j].sum())
        # Inicialización y cálculo de energías
        self.energias = np.zeros((self.img.shape[0], self.img.shape[1]))
        for i in range(1, self.brillos.shape[0] - 1):
            for j in range(1, self.brillos.shape[1] - 1):
                self.energias[i - 1, j - 1] = self.calcularEnergiaPixel(i, j)
                # Se calcula la energía del pixel correspondiente
        # Inicialización de la matriz de costuras
        self.matCosturas = np.array(
            [
                [(-1, 0) for j in range(self.img.shape[1])]
                for i in range(self.img.shape[0])
            ]
        )
        # Calculo de la matriz de costuras
        for i in range(self.img.shape[0]):
            for j in range(self.img.shape[1]):
                self.C(i, j)
        self.costura = []
        self.reconstruirCostura()
        self.img = self.quitarCostura()  # Eliminar costura

    # Devuelve si un indice (i,j) está dentro de los límites de la imagen
    def dentro(self, i, j):
        return (
            True
            if i >= 0
            and i < self.energias.shape[0]
            and j >= 0
            and j < self.energias.shape[1]
            else False
        )

    # Calcula la energía de un píxel
    # @param fil índice válido dentro de la imagen que representa la fila
    # @param col índice válido dentro de la imagen que representa la columna
    # @return devuelve valor numérico que representa la energía de un píxel
    def calcularEnergiaPixel(self, fil, col):
        # Calcula la energía de un pixel dado y la guarda en self.energias (HECHA)
        a = self.brillos[fil - 1][col - 1]
        d = self.brillos[fil][col - 1]
        g = self.brillos[fil + 1][col - 1]
        b = self.brillos[fil - 1][col]
        h = self.brillos[fil + 1][col]
        c = self.brillos[fil - 1][col + 1]
        f = self.brillos[fil][col + 1]
        i = self.brillos[fil + 1][col + 1]
        energiax = a + 2 * d + g - c - 2 * f - i
        energiay = a + 2 * b + c - g - 2 * h - i
        return math.sqrt(energiax**2 + energiay**2)

    # Calcula las energías de la imagen
    def calcularEnergias(self):
        # Calcula todas la energia y la mete en self.energias
        for p in self.costura:
            lst = [p, (p[0], p[1] - 1), (p[0], p[1] - 2), (p[0], p[1] + 1)]
            for e in lst:
                if self.dentro(
                    e[0], e[1]
                ):  # Comprobamos que está dentro de los límites
                    self.energias[e[0], e[1]] = self.calcularEnergiaPixel(e[0], e[1])

    # Calcula el costo acumulado de la matriz de costuras
    def C(self, i, j):
        if i == 0:  # Primera fila toma la energía original
            self.matCosturas[i][j] = (self.energias[i][j], 0)
            return
        estaIzquierda = self.dentro(i - 1, j - 1)
        estaCentro = self.dentro(i - 1, j)
        estaDerecha = self.dentro(i - 1, j + 1)
        if estaIzquierda and estaDerecha:
            lst = [
                self.matCosturas[i - 1][j - 1][0],
                self.matCosturas[i - 1][j][0],
                self.matCosturas[i - 1][j + 1][0],
            ]
            minind = np.argmin(lst)
            self.matCosturas[i][j] = (
                lst[minind] + self.energias[i][j],
                [-1, 0, 1][minind],
            )
        elif estaIzquierda:
            lst = [self.matCosturas[i - 1][j - 1][0], self.matCosturas[i - 1][j][0]]
            minind = np.argmin(lst)
            self.matCosturas[i][j] = (
                lst[minind] + self.energias[i][j],
                [-1, 0][minind],
            )
        elif estaDerecha:
            lst = [self.matCosturas[i - 1][j][0], self.matCosturas[i - 1][j + 1][0]]
            minind = np.argmin(lst)
            self.matCosturas[i][j] = (lst[minind] + self.energias[i][j], [0, 1][minind])
        else:
            self.matCosturas[i][j] = (
                self.matCosturas[i - 1][j][0] + self.energias[i][j],
                0,
            )

    # Reconstruye la costura de menor energía
    def recalcularMatCostura(self, j):
        def noMeSalgo(i, ini, fin):
            if not self.dentro(i, ini):
                ini = ini + 1
            if not self.dentro(i, fin):
                fin = fin - 1

            return ini, fin

        ini, fin = j - 2, j + 1
        for it in range(2):
            ini, fin = noMeSalgo(0, ini, fin)
        for i in range(self.matCosturas.shape[0]):
            for j in range(ini, fin + 1):
                self.C(i, j)
            ini, fin = noMeSalgo(i, ini - 1, fin + 1)

    # Recalcula brillos, energías y costuras
    @timer
    def calcularCostura(self):
        if self.primera:  # Primera iteración
            self.primera = False
            return
        self.brillos = self.quitarCostura(0)
        self.energias = self.quitarCostura(1)
        self.calcularEnergias()
        self.matCosturas = self.quitarCostura(2)
        self.recalcularMatCostura(self.costura[-1][1])
        self.reconstruirCostura()
        self.img = self.quitarCostura()

    # Reconstruye la costura de menor energía desde la última fila hasta la primera
    def reconstruirCostura(self):
        self.costura = []
        i = self.matCosturas.shape[0] - 1
        costuramin = np.argmin(
            [self.matCosturas[i][j][0] for j in range(self.matCosturas.shape[1])]
        )
        # Inicializa la costura con el último píxel de menor energía
        j = costuramin
        # Obtiene el pixel precedente
        while i != -1:
            # Se reconstruye hasta llegar a la primera fila
            self.costura = self.costura + [(i, j)]
            i = i - 1
            j = j + self.matCosturas[i][j][1]  # Se obtiene el siguiente píxel

    # Elimina una costura de la imagen
    # @param ind indica el índice de la matriz a modificar (por defecto la imagen)
    def quitarCostura(self, ind=3):
        mat = [self.brillos, self.energias, self.matCosturas, self.img][ind]
        for e in self.costura:
            i = (
                e[0] + 1 if ind == 0 else e[0]
            )  # Para casos en los que se elimina los brillos
            j = e[1] + 1 if ind == 0 else e[1]
            mat[i, :-1] = np.append(mat[i, :j], mat[i, j + 1 :], axis=0)
        return mat[:, :-1]

    # Guarda la imagen modificada en la ruta especificada
    # @param path es una ruta válida para guardar la imagen
    def guardarImagen(self, path):
        iio.imwrite(path, self.img)
