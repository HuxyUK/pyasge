# -*- coding: utf-8 -*-
import pyasge
import numpy


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)

        """Load a backdrop and then change to mimic scan lines"""
        self.sprite = pyasge.Sprite()
        self.sprite.loadTexture("/data/images/character_robot_idle.png")

        texture = self.sprite.getTexture()
        data = texture.buffer.data

        with numpy.nditer(data[:, ::3], op_flags=["readwrite"], order="C") as it:
            for x in it:
                x[...] = 100

        texture.buffer.upload()
        print(texture.buffer.data[1])

        """Create a non-cached texture, this is memory managed by Python"""
        self.animated_sprite = pyasge.Sprite()
        self.animated_sprite.x = 750
        self.animated_sprite.width = 50
        self.animated_sprite.height = 50
        self.blank_texture = self.renderer.createNonCachedTexture(
            50, 50, pyasge.Texture.Format.RGB, None
        )
        self.animated_sprite.attach(self.blank_texture)

        """Upload pixel data directly"""
        blocks = numpy.full((200, 600), 65, dtype="B")
        self.uploaded_sprite = pyasge.Sprite()
        self.uploaded_sprite.x = 200
        self.uploaded_sprite.y = 200
        self.uploaded_sprite.width = 200
        self.uploaded_sprite.height = 200
        self.uploaded_texture = self.renderer.createNonCachedTexture(
            200, 200, pyasge.Texture.Format.RGB, None
        )
        self.uploaded_sprite.attach(self.uploaded_texture)
        self.uploaded_texture.buffer.upload(blocks, 0)

        print(self.uploaded_texture)
        print(self.blank_texture.buffer)
        repr(self.blank_texture.buffer)

        print(self.blank_texture.width)
        print(self.blank_texture.height)

        print(self.blank_texture.buffer.width)
        print(self.blank_texture.buffer.height)

    def update(self, game_time):
        with numpy.nditer(
            self.blank_texture.buffer.data, op_flags=["readwrite"], order="C"
        ) as it:
            for x in it:
                x[...] = 256 * numpy.random.random()
        self.blank_texture.buffer.upload()
        pass

    def render(self, game_time):
        self.renderer.render(self.sprite)
        self.renderer.render(self.animated_sprite)
        self.renderer.render(self.uploaded_sprite)
        pass


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 800
    settings.window_height = 600
    settings.fixed_ts = 30
    settings.fps_limit = 60
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
