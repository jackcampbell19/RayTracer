
class Color:

    def __init__(self, r, g, b):
        r = min(255, max(0, r))
        g = min(255, max(0, g))
        b = min(255, max(0, b))
        self.value = (r, g, b)

    def getRGB(self):
        return self.value
