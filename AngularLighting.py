
class AngularLighting:

    # Returns light intensity based on the angle
    @staticmethod
    def light_intensity_from_angle(angle):
        deg_factor = abs(angle) / 90
        return -(deg_factor - 1) ** 2 + 1
