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


width = int(sys.argv[1])
height = int(sys.argv[2])
res = int(sys.argv[3])
frames = int(sys.argv[4])
width *= res
height *= res

for f in range(frames):
    file = open('output/data/frame-' + str(f))
    contents = file.readlines()

    l = np.array(list(map(lambda x: int(x), contents[0].split(',')[:-1])))

    # show_image(l, width, height)
    save_image(l, width, height, 'output/images/frame-' + str(f) + ".jpg")
