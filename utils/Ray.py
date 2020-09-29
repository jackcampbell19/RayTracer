
class Ray:

    # Origin and direction vectors
    def __init__(self, origin, direction):
        self.origin = origin
        self.direction = direction
        self.min_t = 0
        self.max_t = 100

    def __repr__(self):
        return f"Ray({self.origin}, {self.direction})"
