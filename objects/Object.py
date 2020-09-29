from Vector import Vector
from Ray import Ray
import numpy as np
from Color import Color
import math


# Generic object class. Consists of an array of "triangles" (each triangle is a list of 3 vectors) and
# and origin point of the object.
class Object:

    def __init__(self):
        self.triangles = []
        self.origin = Vector(0, 0, 0)

    # Computes the normal of a "triangle"
    @staticmethod
    def compute_normal(triangle):
        v1 = triangle[1] - triangle[0]
        v2 = triangle[2] - triangle[0]
        v = np.cross(v1, v2)
        return v / np.linalg.norm(v)

    # Determines if a "triangle" is intersected by a ray. Returns the point
    # at which the intersection happens and the angle of intersection, or None if there is not any.
    @staticmethod
    def triangle_has_intersection(triangle, ray):
        # Moller-Trumbore
        [p1, p2, p3] = triangle
        e1 = p2 - p1
        e2 = p3 - p1
        s = ray.origin - p1
        s1 = np.cross(ray.direction, e2)
        s2 = np.cross(s, e1)
        if np.dot(s1, e1) == 0:
            return None
        scalar = 1.0 / np.dot(s1, e1)
        v = scalar * Vector(np.dot(e2, s2), np.dot(s, s1), np.dot(ray.direction, s2))
        if (v[1] < 0.0 or v[1] > 1.0) or (v[2] < 0.0 or v[1] + v[2] > 1.0) \
                or (v[0] < 0.000001) or v[0] < ray.min_t or v[0] > ray.max_t:
            return None
        # Retrieve the point where the ray intersects the triangle
        intersection_point = ray.origin + v[0] * ray.direction
        # Compute the normal of the triangle
        normal = Object.compute_normal(triangle)
        # Compute the angle of the intersection
        angle = np.arcsin(
            np.dot(ray.direction, normal) /
            np.linalg.norm(ray.direction) * np.linalg.norm(normal)
        ) * 180 / math.pi
        # Return the intersection point and angle of intersection
        return [intersection_point, angle]

    # Generic intersect algorithm. Iterates over triangles in object and returns the color
    # if there was an intersection and None if there is not.
    def intersect(self, ray):
        intersections = []
        # Iterate over all triangles
        for triangle in self.triangles:
            # Check for intersection
            intersect = self.triangle_has_intersection(triangle, ray)
            if intersect:
                intersections.append(intersect)
        # Get the color
        if len(intersections) > 0:
            # Get the closest intersection to the rays origin, i.e. the first item intersected
            [point, angle] = min(intersections, key=lambda x: np.linalg.norm(x[0] - ray.origin))
            # If the angle of intersection is negative, return None, i.e. if the normal
            # of the face is pointed away from the ray
            if angle < 0:
                return None
            deg_factor = abs(angle) / 90
            amp = lambda x: -(x - 1) ** 2 + 1
            deg_factor = amp(deg_factor)
            angle_color = int(255 * deg_factor)
            return Color(angle_color, angle_color, angle_color)
        return None
