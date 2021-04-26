# -*- coding: utf-8 -*-
import pyasge


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)

        self.inputs.addCallback(pyasge.EventType.E_KEY, self.input)
        self.rt = pyasge.RenderTarget(
            self.renderer, 1024 / 2, 768 / 2, pyasge.Texture.Format.RGB, 1
        )

        self.sprite = pyasge.Sprite()
        self.sprite.loadTexture("/data/images/character_robot_idle.png")
        self.sprite.width = 192
        self.sprite.height = 256

        # self.sprite2 = pyasge.Sprite()
        # self.sprite2.loadTexture("/data/images/character_robot_idle.png")

        """create a new sprite to store the render texture"""
        #  blocks = numpy.full((200, 600), 65, dtype='B')
        self.uploaded_sprite = pyasge.Sprite()
        self.uploaded_sprite.x = 192 * 2
        self.uploaded_sprite.y = 256 * 2
        self.uploaded_sprite.width = 1024 / 2
        self.uploaded_sprite.height = 768 / 2
        self.uploaded_sprite.attach(self.rt.buffers[0])
        self.uploaded_sprite.flip_flags = pyasge.Sprite.FlipFlags.FLIP_Y

        """load font and create text instance"""
        self.font = self.renderer.loadFont("/data/fonts/kenvector_future.ttf", 40)
        self.text = pyasge.Text(self.font, "Hello World")

        """track key states"""
        self.keys = {
            pyasge.KEYS.KEY_A: False,
            pyasge.KEYS.KEY_D: False,
            pyasge.KEYS.KEY_W: False,
            pyasge.KEYS.KEY_S: False,
            pyasge.KEYS.KEY_EQUAL: False,
            pyasge.KEYS.KEY_MINUS: False,
        }

    def input(self, event: pyasge.KeyEvent) -> None:
        if event.action is not pyasge.KEYS.KEY_REPEATED:
            self.keys[event.key] = event.action is pyasge.KEYS.KEY_PRESSED

    def update(self, game_time: pyasge.GameTime) -> None:
        pass

    def render(self, game_time: pyasge.GameTime) -> None:
        """ render to texture """
        self.renderer.setRenderTarget(self.rt)
        self.renderer.viewport = pyasge.Viewport(0, 0, 1024 / 2, 768 / 2)
        self.renderer.render(self.sprite)
        #    self.renderer.render(self.sprite2)

        """ render the resultant texture """
        self.renderer.setRenderTarget(None)
        self.renderer.viewport = pyasge.Viewport(0, 0, 1024, 768)
        self.rt.buffers[0].updateMips()
        self.renderer.render(self.uploaded_sprite)


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 1024
    settings.window_height = 768
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
