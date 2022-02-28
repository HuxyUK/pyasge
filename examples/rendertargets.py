# -*- coding: utf-8 -*-
import pyasge


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)

        self.inputs.addCallback(pyasge.EventType.E_KEY, self.input)

        """a sprite to render in to the offscreen target"""
        self.sprite = pyasge.Sprite()
        self.sprite.loadTexture("/data/images/character_robot_idle.png")
        self.sprite.width = 192
        self.sprite.height = 256
        self.sprite.x = 500
        self.sprite.y = 100

        """create a new render target and sprite to store the render texture"""
        self.rt = pyasge.RenderTarget(
            self.renderer, 1024 / 2, 768 / 2, pyasge.Texture.Format.RGB, 1
        )
        self.rt_texture = pyasge.Sprite()
        self.rt_texture.x = 1024 / 2
        self.rt_texture.y = 768 / 2
        self.rt_texture.width = 1024 / 2
        self.rt_texture.height = 768 / 2
        self.rt_texture.attach(self.rt.buffers[0])

        """track key states"""
        self.keys = {
            pyasge.KEYS.KEY_A: False,
            pyasge.KEYS.KEY_D: False,
            pyasge.KEYS.KEY_W: False,
            pyasge.KEYS.KEY_S: False,
            pyasge.KEYS.KEY_EQUAL: False,
            pyasge.KEYS.KEY_MINUS: False,
        }

        """load font and create text instance"""
        self.font = self.renderer.loadFont("/data/fonts/kenvector_future.ttf", 28)
        self.text = pyasge.Text(self.font, "RenderTarget with 50%\nsized viewport")
        self.text.y = self.rt_texture.y + 28
        self.text.x = self.rt_texture.x

    def input(self, event: pyasge.KeyEvent) -> None:
        if event.action is not pyasge.KEYS.KEY_REPEATED:
            self.keys[event.key] = event.action is pyasge.KEYS.KEY_PRESSED

        if event.key == pyasge.KEYS.KEY_ESCAPE:
            self.signal_exit()

    def update(self, game_time: pyasge.GameTime) -> None:
        pass

    def render(self, game_time: pyasge.GameTime) -> None:
        """render to texture"""
        self.renderer.setRenderTarget(self.rt)
        self.renderer.viewport = pyasge.Viewport(0, 0, 1024 / 2, 768 / 2)
        self.renderer.render(self.sprite)

        """ render the resultant texture """
        self.renderer.setRenderTarget(None)
        self.renderer.viewport = pyasge.Viewport(0, 0, 1024, 768)
        self.rt.resolve(0)
        self.renderer.render(self.rt_texture)
        self.renderer.render(self.text)


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 1024
    settings.window_height = 768
    settings.fps_limit = 60
    settings.fixed_ts = 60
    settings.msaa_level = 32
    settings.vsync = pyasge.Vsync.ENABLED
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
