# -*- coding: utf-8 -*-
import pyasge


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)

        """load font and create text instance"""
        self.font = self.renderer.loadFont("/data/fonts/kenvector_future.ttf", 40)
        self.text = pyasge.Text(self.font, "Hello World")

        """change text position"""
        self.text.position = pyasge.Point2D(50, 200)
        self.text.position = [50, 200]
        self.text.position = (50, 200)
        self.text.position.x = 50
        self.text.position.y = 200

        """change text colour"""
        self.text.colour = pyasge.COLOURS.AQUA
        self.text.colour = pyasge.Colour(0, 0, 1)
        self.text.colour = [0, 1, 0]
        self.text.colour = (1, 0, 1)

        """pixel distance checks"""
        print(self.font.pxWide("c", 1))
        print(self.font.pxWide("cat", 1))

        """bounding box checks"""
        print(self.text.local_bounds)
        print(self.text.world_bounds)

        """bounding box checks"""
        self.text.opacity = 0.0
        self.text.scale = 0.75

    def update(self, game_time: pyasge.GameTime) -> None:
        pass

    def render(self, game_time: pyasge.GameTime) -> None:
        self.text.opacity = self.text.opacity + 0.5 * game_time.frame_time
        self.text.scale = self.text.scale + 0.25 * game_time.frame_time

        if self.text.opacity > 1:
            self.text.opacity = 0
            self.text.scale = 0.75

        self.renderer.render(self.text)


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 600
    settings.window_height = 400
    settings.window_mode = pyasge.WindowMode.WINDOWED
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
