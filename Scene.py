import math
import time

import numpy as np
import multiprocessing as mp


# "Scene" represents the 3D scene. The X/Y plane represents the floor and the Z axis represents the vertical direction.
class Scene:

    def __init__(self, camera):
        self.camera = camera
        self.objects = []
        self.default_color_array = (0, 0, 0)
        self.resolution = 1

    def add_object(self, obj):
        self.objects.append(obj)

    def set_resolution(self, res):
        self.resolution = res

    # Render the scene in perspective view
    def render_perspective(self):
        # Get the thread count
        thread_count = 1#mp.cpu_count()
        # Determine how many rows to assign to each thread
        thread_split = int(math.floor(self.camera.height * self.resolution / thread_count))
        # Determine the leftover rows that need to be processed after
        leftover = int(self.camera.height * self.resolution - thread_split * thread_count)
        # Create thread pool
        pool = mp.Pool(thread_count)
        # Construct thread arguments
        args = [(y_start + 1, thread_split)
                for y_start in range(thread_split * thread_count - 1 - thread_split, -2, -thread_split)]
        # Run thread pool with args
        out = np.array(pool.starmap_async(self.render_perspective_async, args).get()).flatten()
        # Run leftover rows
        if leftover > 0:
            leftover_render = self.render_perspective_async(thread_split * thread_count, leftover).flatten()
            out = np.append(leftover_render, out)
        return out

    # Does the heavy lifting for the rendering. Traces the rays through the scene.
    def render_perspective_async(self, y_start, y_count):
        # Scale frame to resolution
        width = self.camera.width * self.resolution
        height = self.camera.height * self.resolution
        # Create output array representing the slice of the image to be rendered.
        output = np.array([[self.default_color_array for _ in range(width)] for _ in range(y_count)])
        # Trace each ray
        for y in range(y_count):
            for x in range(width):
                # Calculate x percentage and y percentage
                px = x / width
                py = (y + y_start) / height
                # Calculate ray
                ray = self.camera.generate_ray(px, py)
                # print(ray)
                for obj in self.objects:
                    # Get color from intersection
                    clr = obj.intersect(ray)
                    if clr:
                        output[y_count - y - 1, width - x - 1] = clr.getRGB()
        return output
