import numpy as np
from Vector import Vector
from Rotate import rotate_vector_z, rotate_vector_y, rotate_vector_x


class Camera:

    # "position" represents the origin of the camera. "rotation" is a
    # vector with x being rotation around the x axis, ect.
    def __init__(self, position, rotation, width, height, focal_length):
        self.position = position
        self.rotation = rotation
        self.width = width
        self.height = height
        self.focal_length = focal_length
        self.frame = self.construct_frame()

    def construct_frame(self):
        # v0 ----- v1
        # |         |
        # v2 ----- v3
        # Generate frame values
        v0 = Vector(-self.width / 2.0,
                    -self.focal_length,
                    self.height / 2.0)
        v1 = Vector(self.width / 2.0,
                    -self.focal_length,
                    self.height / 2.0)
        v2 = Vector(-self.width / 2.0,
                    -self.focal_length,
                    -self.height / 2.0)
        v3 = Vector(self.width / 2.0,
                    -self.focal_length,
                    -self.height / 2.0)
        # Apply rotation to the frame
        v0 = rotate_vector_x(v0, self.rotation[0])
        v0 = rotate_vector_y(v0, self.rotation[1])
        v0 = rotate_vector_z(v0, self.rotation[2])
        v1 = rotate_vector_x(v1, self.rotation[0])
        v1 = rotate_vector_y(v1, self.rotation[1])
        v1 = rotate_vector_z(v1, self.rotation[2])
        v2 = rotate_vector_x(v2, self.rotation[0])
        v2 = rotate_vector_y(v2, self.rotation[1])
        v2 = rotate_vector_z(v2, self.rotation[2])
        v3 = rotate_vector_x(v3, self.rotation[0])
        v3 = rotate_vector_y(v3, self.rotation[1])
        v3 = rotate_vector_z(v3, self.rotation[2])
        # Translate the frame to the camera origin
        v0 = v0 + self.position
        v1 = v1 + self.position
        v2 = v2 + self.position
        v3 = v3 + self.position
        # Update the frame
        return [v0, v1, v2, v3]

    def setPosition(self, vec):
        self.position = vec

    def setRotation(self, rot):
        self.rotation = rot

    # Generates a ray given a position on the frame
    def generate_ray(self, x, y):