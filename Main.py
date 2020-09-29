from Color import Color
from Scene import Scene
from Vector import Vector
from objects.Cube import Cube
from objects.Triangle import Triangle
from Image import render_image, save_image


def render_animation_sequence_rot():
    # Create scene
    scene = Scene()

    # Create object
    obj = Cube(origin=Vector(0, 0, 0), width=20, height=10, length=5)

    # Add object to scene
    scene.addObject(obj)

    # Define params
    width = 20
    height = 20
    resolution = 4
    focal_length = 15

    # Set the camera position and rotation
    for i in range(20):
        print(i / 20)
        # scene.camera.setPosition(Vector(10 + 2 * i, 5 - i / 2, 5))
        # scene.camera.setRotation(Vector(0, 0, -4.5 * i))
        scene.camera.setPosition(Vector(10 + i * 1.2, 20 - i, 5 + i/2))
        scene.camera.setRotation(Vector(0, i, -i * 4.5))

        # Render the scene to an rgb array
        rendered_scene = scene.render_perspective(width, height, resolution, focal_length)

        # Render the image
        save_image(rendered_scene, width * resolution, height * resolution, f"output/{i}.jpg")

def render_animation_sequence():
    # Create scene
    scene = Scene()

    # Create object
    obj = Cube(origin=Vector(0, 0, 0), width=20, height=10, length=5)

    # Add object to scene
    scene.addObject(obj)

    # Define params
    width = 40
    height = 40
    resolution = 3
    focal_length = 6

    # Set the camera position and rotation
    for i in range(20):
        print(i / 20)
        scene.camera.setPosition(Vector(25 - 2 * i, 5, 15 - i))
        scene.camera.setRotation(Vector(0, 0, 0))

        # Render the scene to an rgb array
        rendered_scene = scene.render_perspective(width, height, resolution, focal_length)

        # Render the image
        save_image(rendered_scene, width * resolution, height * resolution, f"output/{i}.jpg")


def render_basic_scene():
    # Create scene
    scene = Scene()

    # Create object
    obj = Cube(origin=Vector(0, 0, 0), width=20, height=10, length=5)

    # Add object to scene
    scene.addObject(obj)

    # Set the camera position and rotation
    scene.camera.setPosition(Vector(25, 5, 15))
    scene.camera.setRotation(Vector(0, 0, 0))

    # Define params
    width = 40
    height = 40
    resolution = 3
    focal_length = 6

    # Render the scene to an rgb array
    rendered_scene = scene.render_perspective(width, height, resolution, focal_length)

    # Render the image
    render_image(rendered_scene, width * resolution, height * resolution)


render_animation_sequence_rot()
