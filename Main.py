from Camera import Camera
from Color import Color
from Scene import Scene
from Vector import Vector
from objects.Cube import Cube
from objects.Triangle import Triangle
from Image import render_image, save_image


def render_animation_sequence_rot():
    # Create camera
    camera = Camera(position=Vector(0, 0, 0),
                    rotation=Vector(0, 0, 0),
                    height=60,
                    width=60,
                    focal_length=30)

    # Create scene
    scene = Scene(camera=camera)

    # Create object
    obj = Cube(origin=Vector(0, 0, 0), width=20, height=10, length=5)

    # Add object to scene
    scene.addObject(obj)

    # Set the camera position and rotation
    for i in range(20):
        print(i / 20)
        scene.camera.setPosition(Vector(10 + i * 1.2, 20 - i, 5 + i/2))
        scene.camera.setRotation(Vector(0, i, -i * 4.5))

        # Render the scene to an rgb array
        rendered_scene = scene.render_perspective()

        # Render the image
        save_image(rendered_scene, scene.camera.width, scene.camera.height, f"output/{i}.jpg")


render_animation_sequence_rot()
