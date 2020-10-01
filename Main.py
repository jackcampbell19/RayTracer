from Camera import Camera
from Scene import Scene
from utils.Vector import Vector
from objects.Cube import Cube
from Image import save_image, show_image
from utils.Rotate import rotate_vector_z
import time


def render_animation_sequence_rot():
    # Create camera
    camera = Camera(position=Vector(0, 0, 0),
                    rotation=Vector(0, 0, 0),
                    height=60,
                    width=60,
                    focal_length=25)

    # Create scene
    scene = Scene(camera=camera)
    scene.set_resolution(1)

    # Create object
    obj = Cube(origin=Vector(-10, 0, -5), width=20, height=10, length=5)

    # Add object to scene
    scene.add_object(obj)

    time_took = None

    # Simulate animation
    for i in range(36):
        print(f"{i}/36 - Time remaining: {'Calculating...' if time_took is None else time_took * (36 - i)}")

        start = time.time()

        camera_position_vector = Vector(0, 30, 10)
        camera_position_vector = rotate_vector_z(camera_position_vector, -10 * i)

        scene.camera.setPosition(camera_position_vector)
        scene.camera.setRotation(Vector(25, 0, -10 * i))

        # Render the scene to an rgb array
        rendered_scene = scene.render_perspective()

        # Render the image
        save_image(rendered_scene, scene.camera.width * scene.resolution, scene.camera.height * scene.resolution, f"output/{i}.jpg")

        end = time.time()
        time_took = end - start
        time_took = time_took / 60


def render_show_single_frame():
    # Create camera
    camera = Camera(position=Vector(0, 0, 0),
                    rotation=Vector(0, 0, 0),
                    height=60,
                    width=60,
                    focal_length=25)

    # Create scene
    scene = Scene(camera=camera)
    scene.set_resolution(4)

    # Create object
    obj = Cube(origin=Vector(-10, 0, -5), width=20, height=10, length=5)

    # Add object to scene
    scene.add_object(obj)

    camera_position_vector = Vector(0, 30, 10)
    camera_position_vector = rotate_vector_z(camera_position_vector, -70)
    scene.camera.setPosition(camera_position_vector)
    scene.camera.setRotation(Vector(25, 0, -70))

    s = time.time()

    # Render the scene to an rgb array
    rendered_scene = scene.render_perspective()

    e = time.time()

    print(f"{scene.camera.width * scene.resolution}x{scene.camera.height * scene.resolution} took {e - s} seconds")

    # Render the image
    show_image(rendered_scene, scene.camera.width * scene.resolution, scene.camera.height * scene.resolution)



render_show_single_frame()
