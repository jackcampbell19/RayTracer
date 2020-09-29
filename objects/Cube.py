from objects.Object import Object
from utils.Vector import Vector


class Cube(Object):

    def __init__(self, origin, width, length, height):
        super(Cube, self).__init__()
        self.origin = origin

        p0 = origin
        p1 = origin + Vector(width, 0, 0)
        p2 = origin - Vector(0, length, 0)
        p3 = origin + Vector(width, 0, 0) - Vector(0, length, 0)

        p4 = origin + Vector(0, 0, height)
        p5 = origin + Vector(0, 0, height) + Vector(width, 0, 0)
        p6 = origin + Vector(0, 0, height) - Vector(0, length, 0)
        p7 = origin + Vector(0, 0, height) + Vector(width, 0, 0) - Vector(0, length, 0)

        self.triangles.append([p0, p2, p1])
        self.triangles.append([p1, p2, p3])

        self.triangles.append([p0, p5, p4])
        self.triangles.append([p0, p1, p5])

        self.triangles.append([p2, p0, p4])
        self.triangles.append([p4, p6, p2])

        self.triangles.append([p2, p7, p3])
        self.triangles.append([p2, p6, p7])

        self.triangles.append([p1, p3, p5])
        self.triangles.append([p3, p7, p5])

        self.triangles.append([p5, p7, p6])
        self.triangles.append([p4, p5, p6])
