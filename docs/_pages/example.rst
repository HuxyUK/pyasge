Example Game
============================

.. code-block:: python

   # -*- coding: utf-8 -*-
   import pyasge


   class MyASGEGame(pyasge.ASGEGame):
       def __init__(self, settings):
           pyasge.ASGEGame.__init__(self, settings)

           """register key handler for key press events"""
           self.inputs.addCallback(pyasge.EventType.E_KEY, self.input)

           """create a new sprite to store the render texture"""
           self.sprite = pyasge.Sprite()
           self.sprite.loadTexture("/data/sprite.png")
           self.sprite.width = 200
           self.sprite.height = 200

           """load font and create text instance"""
           self.font = self.renderer.loadFont("/data/fonts/kenvector_future.ttf", 40)
           self.text = pyasge.Text(self.font, "Hello World")
           self.text.position = pyasge.Point2D(200, 200)

           """track key states"""
           self.keys = {
               pyasge.KEYS.KEY_A: False,
               pyasge.KEYS.KEY_D: False,
               pyasge.KEYS.KEY_W: False,
               pyasge.KEYS.KEY_S: False,
           }

       def input(self, event: pyasge.KeyEvent) -> None:
           if event.key is not pyasge.KEYS.KEY_REPEATED:
               self.keys[event.key] = event action is pyasge.KEYS.KEY_PRESSED

       def update(self, game_time: pyasge.GameTime) -> None:
           pass

       def render(self, game_time: pyasge.GameTime) -> None:
           self.renderer.render(self.sprite)
           self.renderer.render(self.text)


   def main():
       settings = pyasge.GameSettings()
       settings.window_width = 1024
       settings.window_height = 768
       game = MyASGEGame(settings)
       game.run()


   if __name__ == "__main__":
       main()
