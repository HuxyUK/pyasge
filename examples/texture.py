# -*- coding: utf-8 -*-
import pyasge


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)
        self.texture = self.renderer.createNonCachedTexture(
            "/data/images/background.jpg"
        )
        self.blank_texture = self.renderer.createNonCachedTexture(
            50, 50, pyasge.Texture.Format.RGB, None
        )
        print(self.blank_texture)
        print(self.blank_texture.format)
        print(self.blank_texture.width)
        print(self.blank_texture.height)
        self.blank_texture.format = self.blank_texture.format

    def update(self, game_time: pyasge.GameTime):
        pass

    def render(self, game_time: pyasge.GameTime):
        self.renderer.render(self.texture, 50, 50)
        self.renderer.render(self.blank_texture, 50, 50)


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 800
    settings.window_height = 600
    game = MyASGEGame(settings)
    print(pyasge.Texture._test_texture_format_enum(pyasge.Texture.Format.RGB))
    game.run()


if __name__ == "__main__":
    main()
