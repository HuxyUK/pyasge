# -*- coding: utf-8 -*-
import pyasge

from .gamedata import GameData
from .gameobject import GameObject
from .gamestate import GameState, GameStateID


class GameScene(GameState):
    def __init__(self, data: GameData) -> None:
        super().__init__(data)
        self.id = GameStateID.GAMEPLAY

        self.player = GameObject("/data/images/player_ship_type_l.png")
        self.player.sprite.scale = 1
        self.player.sprite.z_order = 50
        self.player.lives = 3

        self.enemy = GameObject("/data/images/enemy_type_e.png")
        self.enemy.sprite.scale = 1
        self.enemy.sprite.x = 200
        self.enemy.velocity.y = 2

        self.move_handle = data.inputs.addCallback(
            pyasge.EventType.E_KEY, self.key_handler
        )

    def key_handler(self, event: pyasge.KeyEvent) -> None:
        if event.key is pyasge.KEYS.KEY_W and event.action is pyasge.KEYS.KEY_PRESSED:
            self.player.velocity.y = -0.5 * 1000

        if event.key is pyasge.KEYS.KEY_W and event.action is pyasge.KEYS.KEY_RELEASED:
            self.player.velocity.y = 0

        if event.key is pyasge.KEYS.KEY_S:
            if event.action is pyasge.KEYS.KEY_PRESSED:
                self.player.velocity.y = 0.5 * 1000
            elif event.action is pyasge.KEYS.KEY_RELEASED:
                self.player.velocity.y = 0

        if event.key is pyasge.KEYS.KEY_A:
            if event.action is pyasge.KEYS.KEY_PRESSED:
                self.player.velocity.x = -0.5 * 1000
            elif event.action is pyasge.KEYS.KEY_RELEASED:
                self.player.velocity.x = 0

        if event.key is pyasge.KEYS.KEY_D:
            if event.action is pyasge.KEYS.KEY_PRESSED:
                self.player.velocity.x = 0.5 * 1000
            elif event.action is pyasge.KEYS.KEY_RELEASED:
                self.player.velocity.x = 0

    def update(self, inputs, game_time: pyasge.GameTime) -> GameStateID:
        # first connected gamepad
        if inputs.getGamePad().connected:
            self.player.velocity.x = inputs.getGamePad().AXIS_LEFT_X * 500
            self.player.velocity.y = inputs.getGamePad().AXIS_LEFT_Y * 500

        self.player.update(game_time)
        self.enemy.update(game_time)

        if self.enemy.sprite.y >= 1080:
            self.enemy.sprite.y = 0 - 50

        player_bounds = self.player.sprite.getWorldBounds()
        enemy_bounds = self.enemy.sprite.getWorldBounds()

        if (
            player_bounds.v1.x <= enemy_bounds.v2.x
            and player_bounds.v2.x >= enemy_bounds.v1.x
        ):
            if (
                player_bounds.v1.y <= enemy_bounds.v3.y
                and player_bounds.v3.y >= enemy_bounds.v1.y
            ):
                self.player.lives = self.player.lives - 1
                self.respawn()

        if self.player.lives < 1:
            return GameStateID.GAME_OVER

        return self.id

    def fixed_update(self, inputs, game_time: pyasge.GameTime):
        pass

    def respawn(self):
        self.player.sprite.x = 100
        self.player.sprite.y = 500

    def render(self, renderer, game_time):
        self.gamedata.background.render(renderer)

        self.gamedata.parallax[0].sprite.src_rect[1] = (
            self.gamedata.parallax[0].sprite.src_rect[1] - 40.00 * game_time.frame_time
        )
        self.gamedata.parallax[1].sprite.src_rect[1] = (
            self.gamedata.parallax[1].sprite.src_rect[1] - 80.00 * game_time.frame_time
        )

        for bg in self.gamedata.parallax:
            bg.render(renderer)

        self.player.render(renderer)
        self.enemy.render(renderer)
