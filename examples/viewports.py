# -*- coding: utf-8 -*-
import pyasge


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)
        # self.toggleFPS()

        self.camera = pyasge.Camera(384 * 0.5, 256)
        self.camera.lookAt([192 * 0.5, 128])
        self.sprite = pyasge.Sprite()
        self.sprite.loadTexture("/data/images/character_zombie_idle.png")
        self.sprite.scale = 1.0
        self.sprite.y = -25

        self.sprite2 = pyasge.Sprite()
        self.sprite2.loadTexture("/data/images/character_robot_idle.png")
        self.sprite2.scale = 1.0
        self.sprite2.y = -25

        """load font and create text instance"""
        self.font = self.renderer.loadFont("/data/fonts/kenvector_future.ttf", 40)
        self.text = pyasge.Text(self.font, "Hello World")

    def update(self, game_time) -> None:
        self.camera.update(game_time)

    def render(self, game_time):
        self.renderer.setProjectionMatrix(self.camera.view)
        self.renderer.viewport = pyasge.Viewport(0, 0, 384 / 2, 256)
        self.renderer.render(self.sprite)
        self.renderer.viewport = pyasge.Viewport(384 / 2, 0, 384 / 2, 256)
        self.renderer.render(self.sprite2)


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 384
    settings.window_height = 256
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
