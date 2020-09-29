from objects.Object import Object


class Triangle(Object):

    def __init__(self, a, b, c, color):
        self.points = [a, b, c]
        self.color = color

    def intersect(self, ray):
        intersect = self.get_triangle_intersection(self.points, ray)
        if not intersect:
            return None
        return self.color
