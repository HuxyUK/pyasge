# -*- coding: utf-8 -*-
import pyasge


class GameObject:
    def __init__(self, texture):
        self.sprite = pyasge.Sprite()
        self.sprite.loadTexture(texture)
        self.velocity = pyasge.Point2D(0, 0)
        self.sprite.setMagFilter(pyasge.MagFilter.NEAREST)

        self.colour = pyasge.Colour(0, 0, 0)

    def update(self, game_time):
        self.sprite.x += self.velocity.x * 10
        self.sprite.y += self.velocity.y * 10

    def render(self, renderer):
        renderer.render(self.sprite)
        pass
