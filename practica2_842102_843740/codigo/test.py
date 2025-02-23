# Algoritmia básica - Práctica 2
# Nicolás de Rivas (843740)
# Cristina Embid (842102)
import imageio.v3 as iio
import numpy as np

if __name__ == "__main__":
    altura = 100
    anchura = 30
    img = np.zeros((altura, anchura, 3), dtype=np.uint8)
    colores = [[0, 0, 0], [255, 255, 255]]
    for i in range(anchura):
        img[:, i] = np.array([colores[i % len(colores)] for j in range(altura)])
    iio.imwrite("../pruebas/test.bmp", img)
