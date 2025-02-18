import imageio.v3 as iio
import numpy as np
from costuras import *
import sys

if __name__ == "__main__":
    img = iio.imread("imagen.tiff")
    colores = [[0, 0, 0, 100], [0, 0, 100, 100], [0, 100, 100, 0], [0,100,0,100]]
    print(img.shape)
    for i in range(img.shape[1]):
        img[:, i] = np.array([colores[i%4] for j in range(img.shape[0])])
    iio.imwrite("out.tiff", img)
    exit(0)
