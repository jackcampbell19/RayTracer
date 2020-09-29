import math

from Camera import Camera
from Vector import Vector
from Ray import Ray
import numpy as np
import multiprocessing as mp


# "Scene" represents the 3D scene. The X/Y plane represents the floor and the Z axis represents the vertical direction.
class Scene:

    def __init__(self):
        self.camera = Camera(position=Vector(0, 0, 0), rotation=Vector(0, 0, 0))
        self.objects = []

    def addObject(self, object):
        self.objects.append(object)

    # Render the scene in perspective
    def render_perspective(self, width, height, resolution, focal_length):
        # Expand render output to resolution
        height *= resolution
        width *= resolution
        # Generate rays from camera through frame and into scene using parallel process
        # Get the thread count
        thread_count = mp.cpu_count()
        # Determine how many rows to assign to each thread
        thread_split = int(math.floor(height / thread_count))
        # Determine the leftover rows that need to be processed after
        leftover = int(height - thread_split * thread_count)
        # Create thread pool
        pool = mp.Pool(thread_count)
        # Construct thread arguments
        args = [(y_start + 1, thread_split, width, height, v0, v1, v2, v3, (0, 0, 0))
                for y_start in range(thread_split * thread_count - 1 - thread_split, -2, -thread_split)]
        # Run thread pool with args
        out = np.array(pool.starmap_async(self.render_perspective_async, args).get()).flatten()
        # Run leftover rows
        if leftover > 0:
            leftover_render = self.render_perspective_async(thread_split * thread_count, leftover, width,
                                                            height, v0, v1, v2, v3, (0, 0, 0)).flatten()
            out = np.append(leftover_render, out)
        return out

    # Does the heavy lifting for the rendering. Traces the rays through the scene.
    def render_perspective_async(self, y_start, y_count, width, height, v0, v1, v2, v3, default_color_array):
        # Create output array representing the slice of the image to be rendered.
        output = np.array([[default_color_array for _ in range(width)] for _ in range(y_count)])
        # Trace each ray
        for y in range(y_count):
            for x in range(width):
                # Calculate x percentage and y percentage
                py = (y + y_start) / height
                px = x / width
                # Calculate point on frame to trace ray through
                tx0 = v0 * px + v1 * (1.0 - px)
                tx1 = v2 * px + v3 * (1.0 - px)
                fp = tx0 * py + tx1 * (1.0 - py)
                # Calculate ray
                direction = fp - self.camera.position
                ray = Ray(self.camera.position, direction)
                for obj in self.objects:
                    # Get color from intersection
                    clr = obj.intersect(ray)
                    if clr:
                        output[y_count - y - 1, width - x - 1] = clr.getRGB()
        return output
