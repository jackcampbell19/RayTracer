import numpy as np
import math


def rotate_vector_x(v, r):
    m = np.array([
        [1, 0, 0],
        [0, math.cos(r * math.pi / 180), -math.sin(r * math.pi / 180)],
        [0, math.sin(r * math.pi / 180), math.cos(r * math.pi / 180)]
    ])
    return m.dot(v)


def rotate_vector_y(v, r):
    m = np.array([
        [math.cos(r * math.pi / 180), 0, math.sin(r * math.pi / 180)],
        [0, 1, 0],
        [-math.sin(r * math.pi / 180), 0, math.cos(r * math.pi / 180)]
    ])
    return m.dot(v)


def rotate_vector_z(v, r):
    m = np.array([
        [math.cos(r * math.pi / 180), -math.sin(r * math.pi / 180), 0],
        [math.sin(r * math.pi / 180), math.cos(r * math.pi / 180), 0],
        [0, 0, 1]
    ])
    return m.dot(v)
