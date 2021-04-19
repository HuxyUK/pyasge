# -*- coding: utf-8 -*-
import pyasge


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)

        self.camera = pyasge.Camera(1024, 768)
        self.camera.lookAt(pyasge.Point2D(0, 0))

        self.bg = pyasge.Sprite()
        self.bg.loadTexture("/data/images/background.png")
        self.bg.z_order = -10
        self.bg.x = -750
        self.bg.y = -500

        self.sprite = pyasge.Sprite()
        self.sprite.loadTexture("/data/images/character_zombie_idle.png")
        self.inputs.addCallback(pyasge.EventType.E_KEY, self.input)

        """load font and create text instance"""
        self.font = self.renderer.loadFont("/data/fonts/kenvector_future.ttf", 40)
        self.text = pyasge.Text(self.font, "[BRAINS]")
        self.ui_text = pyasge.Text(self.font, "Lives: XXX")
        self.ui_text.position = [1020 - self.ui_text.width, 35]
        self.ui_text.colour = pyasge.COLOURS.CHOCOLATE

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
        if self.keys[pyasge.KEYS.KEY_W]:
            self.camera.translateY(-500 * game_time.fixed_timestep)
        if self.keys[pyasge.KEYS.KEY_S]:
            self.camera.translateY(+500 * game_time.fixed_timestep)
        if self.keys[pyasge.KEYS.KEY_A]:
            self.camera.translateX(-500 * game_time.fixed_timestep)
        if self.keys[pyasge.KEYS.KEY_D]:
            self.camera.translateX(+500 * game_time.fixed_timestep)
        if self.keys[pyasge.KEYS.KEY_EQUAL]:
            self.camera.translateZ(+0.5 * game_time.fixed_timestep)
        if self.keys[pyasge.KEYS.KEY_MINUS]:
            self.camera.translateZ(-0.5 * game_time.fixed_timestep)

        self.camera.update(game_time)

    def render(self, game_time: pyasge.GameTime) -> None:
        self.renderer.setProjectionMatrix(self.camera.view)
        self.renderer.render(self.bg)
        self.renderer.render(self.sprite)
        self.renderer.render(self.text)

        ui_camera = pyasge.CameraView()
        ui_camera.max_x = 1024
        ui_camera.max_y = 768
        self.renderer.setProjectionMatrix(ui_camera)
        self.renderer.render(self.ui_text)


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 1024
    settings.window_height = 768
    settings.fixed_ts = 60
    settings.fps_limit = 60
    settings.vsync = pyasge.Vsync.ENABLED
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
