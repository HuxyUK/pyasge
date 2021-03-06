# -*- coding: utf-8 -*-
import pyasge
import sys
from pathlib import Path

from game.gamedata import GameData
from game.gamemenu import GameMenu
from game.gameobject import GameObject
from game.gameover import GameOver
from game.gamescene import GameScene
from game.gamestate import GameStateID

from pyasge import Texture


path = str(Path(Path(__file__).parent.absolute()).parent.absolute())
sys.path.insert(0, path)


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)
        self.gamedata = GameData()
        self.gamedata.inputs = self.inputs
        self.scene = GameMenu(self.gamedata)
        self.handler = self.inputs.addCallback(
            pyasge.EventType.E_KEY, self.scene.key_handler
        )

        self.inputs.setCursorMode(pyasge.CursorMode.HIDDEN)

        self.gamedata.background = GameObject("/data/images/background.jpg")
        self.gamedata.background.sprite.z_order = -50
        self.gamedata.background.sprite.width = 608
        self.gamedata.background.sprite.height = 1080

        self.gamedata.parallax = []
        self.gamedata.parallax.append(GameObject("/data/images/spr_stars00.png"))
        self.gamedata.parallax.append(GameObject("/data/images/spr_stars01.png"))
        self.gamedata.parallax[0].sprite.z_order = -20
        self.gamedata.parallax[0].sprite.width = 608
        self.gamedata.parallax[0].sprite.height = 1080
        self.gamedata.parallax[0].sprite.src_rect[3] = 1080 / 6
        self.gamedata.parallax[0].sprite.texture.setUVMode(
            Texture.UVWrapMode.REPEAT, Texture.UVWrapMode.REPEAT
        )

        self.gamedata.parallax[1].sprite.z_order = -10
        self.gamedata.parallax[1].sprite.width = 608
        self.gamedata.parallax[1].sprite.height = 1080
        self.gamedata.parallax[1].sprite.src_rect[3] = 1080 / 6
        self.gamedata.parallax[1].sprite.texture.setUVMode(
            Texture.UVWrapMode.REPEAT, Texture.UVWrapMode.REPEAT
        )

        self.gamedata.font = self.renderer.loadFont(
            "/data/fonts/kenvector_future.ttf", 96
        )

    def update(self, game_time: pyasge.GameTime):

        if self.inputs.getGamePad(0).connected and self.inputs.getGamePad(0).A:
            self.signalExit()

        new_state = self.scene.update(self.inputs, game_time)
        if new_state != self.scene.id:
            self.inputs.removeCallback(self.handler)
            if new_state == GameStateID.GAMEPLAY:
                self.scene = GameScene(self.gamedata)
                self.handler = self.inputs.addCallback(
                    pyasge.EventType.E_KEY, self.scene.key_handler
                )
            elif new_state == GameStateID.GAME_OVER:
                self.scene = GameOver(self.gamedata)
                self.handler = self.inputs.addCallback(
                    pyasge.EventType.E_KEY, self.scene.key_handler
                )
            else:
                self.signal_exit()

    def fixed_update(self, game_time: pyasge.GameTime):
        self.scene.fixed_update(self.inputs, game_time)

    def render(self, game_time: pyasge.GameTime):
        self.scene.render(self.renderer, game_time)


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 608
    settings.window_height = 1080
    settings.window_mode = pyasge.WindowMode.WINDOWED
    settings.fixed_ts = 60
    settings.fps_limit = 280
    settings.vsync = pyasge.Vsync.DISABLED
    settings.msaa_level = 32

    pyasge.LOG("HELLO LOG CHANNEL")
    pyasge.ERROR("HELLO ERROR CHANNEL")
    pyasge.DEBUG("HELLO DEBUG CHANNEL")
    pyasge.TRACE("HELLO TRACE CHANNEL")
    pyasge.INFO("HELLO INFO CHANNEL")
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
