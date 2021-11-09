# -*- coding: utf-8 -*-
import pyasge


class GameObject:
    def __init__(self, texture):
        self.sprite = pyasge.Sprite()
        self.sprite.loadTexture(texture)
        self.velocity = pyasge.Point2D(0, 0)
        self.sprite.setMagFilter(pyasge.MagFilter.NEAREST)

        self.colour = pyasge.Colour(0, 0, 0)

    def update(self, game_time: pyasge.GameTime):
        self.sprite.x += self.velocity.x * game_time.frame_time
        self.sprite.y += self.velocity.y * game_time.frame_time

    def render(self, renderer):
        renderer.render(self.sprite)
        pass
