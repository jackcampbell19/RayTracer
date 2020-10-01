from PIL import Image
import numpy as np


# Renders and shows an image
def show_image(np_array, width, height):
    b = bytes(np.uint8(np_array.reshape(width * height, 3).tolist()))
    out = Image.frombytes('RGB', (width, height), b)
    out.show()


def save_image(np_array, width, height, filepath):
    b = bytes(np.uint8(np_array.reshape(width * height, 3).tolist()))
    out = Image.frombytes('RGB', (width, height), b)
    out.save(filepath)
