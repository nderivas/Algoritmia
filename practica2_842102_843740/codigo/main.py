import imageio.v3 as iio
import numpy as np
from costuras import *
import sys

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Uso: costuras <n> <archivo> <salida>")
        exit(1)
    img = iio.imread(sys.argv[2])
    sys.setrecursionlimit(img.shape[0]*img.shape[1])
    for i in range(int(sys.argv[1])):
        costura = encontrarCostura(img)
        img = quitarCostura(costura, img)
    iio.imwrite(sys.argv[3], img)
    exit(0)
