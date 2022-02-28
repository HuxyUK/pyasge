# -*- coding: utf-8 -*-
import pyasge


def key_handler(event: pyasge.KeyEvent) -> None:
    print("===============")
    print(f"key press received. {event.key}")
    print(f"mods received. {event.mods}")

    if event.mods & pyasge.KEYS.MOD_SHIFT:
        print("Shift set")


def move_event(event: pyasge.MoveEvent) -> None:
    print("===============")
    print("mouse moved event")
    print(f"x position: {event.x}")
    print(f"y position: {event.y}")


def click_event(event: pyasge.ClickEvent) -> None:
    print("===============")
    print(f"x button: {event.button}")
    print(f"action: {event.action}")
    print(f"x position: {event.x} \ny position: {event.y}")

    if event.mods & pyasge.KEYS.MOD_SHIFT:
        print("Shift set")


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)
        self.inputs.addCallback(pyasge.EventType.E_KEY, key_handler)
        self.inputs.addCallback(pyasge.EventType.E_MOUSE_MOVE, move_event)
        self.inputs.addCallback(pyasge.EventType.E_MOUSE_CLICK, click_event)
        self.buttons: dict[str, bool] = {"A": False, "B": False}
        self.gamepad: pyasge.GamePad = None

    def update(self, game_time: pyasge.GameTime) -> None:

        # first connected gamepad
        if self.inputs.getGamePad().connected:
            pyasge.INFO(self.inputs.getGamePad().name)

        # specific gamepad via its index
        if self.inputs.getGamePad(2).connected:
            pyasge.INFO(self.inputs.getGamePad(2).name)

        # all connected gamepads
        for gamepad in self.inputs.gamepads:
            pyasge.INFO(gamepad.name)

        for gamepad in self.inputs.gamepads:
            if self.gamepad:
                if not self.gamepad.A and gamepad.A:
                    pyasge.INFO("A pressed")
                elif self.gamepad.A and gamepad.A:
                    pyasge.INFO("A held")
                elif self.gamepad.A and not gamepad.A:
                    pyasge.INFO("A released")

            # update the gamepad states so we can track changes
            self.update_gamepad_state(gamepad)

    def update_gamepad_state(self, pad: pyasge.GamePad) -> None:
        self.gamepad = pad

    def render(self, game_time: pyasge.GameTime) -> None:
        pass


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 600
    settings.window_height = 400
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
