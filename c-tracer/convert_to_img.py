from PIL import Image
import numpy as np
import sys


# Renders and shows an image
def show_image(np_array, width, height):
    b = bytes(np.uint8(np_array.reshape(width * height, 3).tolist()))
    out = Image.frombytes('RGB', (width, height), b)
    out.show()


def save_image(np_array, width, height, filepath):
    b = bytes(np.uint8(np_array.reshape(width * height, 3).tolist()))
    out = Image.frombytes('RGB', (width, height), b)
    out.save(filepath)


fn = str(sys.argv[1])
width = int(sys.argv[2])
height = int(sys.argv[3])
res = int(sys.argv[4])

file = open(fn)
contents = file.readlines()
width *= res
height *= res

l = np.array(list(map(lambda x: int(x), contents[0].split(',')[:-1])))

show_image(l, width, height)
