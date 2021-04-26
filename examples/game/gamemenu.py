# -*- coding: utf-8 -*-
import pyasge
from .gamedata import GameData
from .gameobject import GameObject
from .gamestate import GameState, GameStateID


class GameMenu(GameState):
    def __init__(self, data: GameData) -> None:
        super().__init__(data)
        self.id = GameStateID.START_MENU
        self.user_clicked = False

        self.start_button = GameObject("/data/images/menu_buttons.png")
        self.start_button.sprite.z_order = 0
        self.start_button.sprite.src_rect = [194, 165, 613, 203]
        self.start_button.sprite.x = 50
        self.start_button.sprite.y = 300
        self.start_button.sprite.width = 500
        self.start_button.sprite.height = 200
        self.start_button.clicked = False

        self.exit_button = GameObject("/data/images/menu_buttons.png")
        self.exit_button.sprite.z_order = 0
        self.exit_button.sprite.src_rect = [194, 400, 613, 203]
        self.exit_button.sprite.x = 50
        self.exit_button.sprite.y = 600
        self.exit_button.sprite.width = 500
        self.exit_button.sprite.height = 200
        self.exit_button.clicked = False

        self.mouse_cursor = GameObject("/data/images/black_cursor.png")
        self.mouse_cursor.sprite.z_order = 5
        self.mouse_cursor.sprite.src_rect = [36, 35, 47, 42]
        self.mouse_cursor.sprite.height = 42
        self.mouse_cursor.sprite.width = 47

        cursor_pos = self.gamedata.inputs.getCursorPos()
        self.mouse_cursor.sprite.x = cursor_pos.x
        self.mouse_cursor.sprite.y = cursor_pos.y

        self.gamedata.inputs.setCursorMode(pyasge.CursorMode.HIDDEN)
        self.move_handle = self.gamedata.inputs.addCallback(
            pyasge.EventType.E_MOUSE_MOVE, self.move_event
        )
        self.click_handle = self.gamedata.inputs.addCallback(
            pyasge.EventType.E_MOUSE_CLICK, self.click_event
        )

    def update(self, inputs, game_time: pyasge.GameTime) -> GameStateID:
        if self.start_button.clicked is True:
            self.gamedata.inputs.removeCallback(self.move_handle)
            self.gamedata.inputs.removeCallback(self.click_handle)
            return GameStateID.GAMEPLAY

        if self.exit_button.clicked is True:
            self.gamedata.inputs.removeCallback(self.move_handle)
            self.gamedata.inputs.removeCallback(self.click_handle)
            return GameStateID.EXIT_GAME

        self.gamedata.parallax[0].sprite.src_rect[1] = (
            self.gamedata.parallax[0].sprite.src_rect[1] - 0.50
        )
        self.gamedata.parallax[1].sprite.src_rect[1] = (
            self.gamedata.parallax[1].sprite.src_rect[1] - 1.00
        )
        return self.id

    def render(self, renderer: pyasge.Renderer, gametime: pyasge.GameTime) -> None:
        self.gamedata.background.render(renderer)

        for bg in self.gamedata.parallax:
            bg.render(renderer)

        renderer.render(self.start_button.sprite)
        renderer.render(self.exit_button.sprite)
        renderer.render(self.mouse_cursor.sprite)

    def key_handler(self, event: pyasge.KeyEvent) -> None:
        self.user_clicked = True

    def move_event(self, event: pyasge.MoveEvent) -> None:
        self.mouse_cursor.sprite.x = event.x
        self.mouse_cursor.sprite.y = event.y

    def click_event(self, event: pyasge.ClickEvent) -> None:
        cursor_pos = pyasge.Point2D(event.x, event.y)
        print(cursor_pos)
        bounds = self.start_button.sprite.getWorldBounds()

        if bounds.v1.x <= cursor_pos.x <= bounds.v2.x:
            if bounds.v1.y <= cursor_pos.y <= bounds.v3.y:
                self.start_button.clicked = True
                return

        bounds = self.exit_button.sprite.getWorldBounds()

        if bounds.v1.x <= cursor_pos.x <= bounds.v2.x:
            if bounds.v1.y <= cursor_pos.y <= bounds.v3.y:
                self.exit_button.clicked = True
