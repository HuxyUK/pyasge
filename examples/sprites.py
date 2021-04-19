# -*- coding: utf-8 -*-
import pyasge


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)

        """load background"""
        self.sprite = pyasge.Sprite()
        if not self.sprite.loadTexture("/data/images/menu_buttons.png"):
            print("error: failed to load")

        """print sprite dimensions"""
        dims = self.sprite.dimensions()
        print(dims)

        """print sprite colour"""
        print(self.sprite.colour)
        self.sprite.colour = pyasge.COLOURS.PINK
        print(self.sprite.colour)

        """sprite sheet"""
        self.sprite_sheet = pyasge.Sprite()
        self.sprite_sheet.loadTexture("/data/images/character_robot_idle.png")
        self.sprite_sheet.src_rect[pyasge.Sprite.SourceRectIndex.START_X] = 227
        self.sprite_sheet.src_rect[pyasge.Sprite.SourceRectIndex.LENGTH_X] = 44
        self.sprite_sheet.width = 44

        self.flipped_sprite = pyasge.Sprite()
        self.flipped_sprite.loadTexture("/data/images/character_zombie_idle.png")
        self.flipped_sprite.x = 300
        self.flipped_sprite.y = 100
        self.flipped_sprite.flip_flags = pyasge.Sprite.FlipFlags.FLIP_X

        bb = self.flipped_sprite.getLocalBounds()
        print(bb)
        gb = self.flipped_sprite.getWorldBounds()
        print(gb)

    def update(self, game_time: pyasge.GameTime) -> None:
        pass

    def render(self, game_time: pyasge.GameTime) -> None:
        self.renderer.render(self.sprite)
        self.renderer.render(self.sprite_sheet)
        self.renderer.render(self.flipped_sprite)
        pass


def main():
    settings = pyasge.GameSettings()
    settings.vsync = pyasge.Vsync.DISABLED
    settings.fps_limit = 320
    settings.window_width = 800
    settings.window_height = 600
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
