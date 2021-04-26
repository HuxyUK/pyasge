# -*- coding: utf-8 -*-
import pyasge


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)

        """sprite sheet"""
        self.sprite_sheet = pyasge.Sprite()
        self.sprite_sheet.loadTexture("/data/Textures/spritesheet.png")
        self.sprite_sheet.src_rect[pyasge.Sprite.SourceRectIndex.START_X] = 227
        self.sprite_sheet.src_rect[pyasge.Sprite.SourceRectIndex.LENGTH_X] = 44
        self.sprite_sheet.width = 44
        self.sprite_sheet.x = 200
        self.sprite_sheet.y = 50
        self.sprite_sheet.scale = 5
        self.sprite_sheet.setMagFilter(pyasge.MagFilter.NEAREST)

    def update(self, game_time: pyasge.GameTime):
        pass

    def render(self, game_time: pyasge.GameTime):
        self.renderer.render(self.sprite_sheet)
        pass


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 600
    settings.window_height = 400
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
