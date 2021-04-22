# -*- coding: utf-8 -*-
import pyasge

frag_shader = """
#version 330 core
#define FRAG_COLOUR     0
in VertexData
{
    vec2    uvs;
    vec4    rgba;
} fs_in;

uniform float alpha;
uniform sampler2D image;
layout  (location = FRAG_COLOUR, index = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(fs_in.rgba.rgb, alpha) * texture(image, fs_in.uvs);
}
"""


class MyASGEGame(pyasge.ASGEGame):
    def __init__(self, settings):
        pyasge.ASGEGame.__init__(self, settings)

        self.inline_shader = self.renderer.initPixelShader(frag_shader)

        self.sprite = pyasge.Sprite()
        self.sprite.loadTexture("/data/images/character_robot_idle.png")
        self.sprite.width = 332
        self.sprite.height = 452

        self.alpha_sprite = pyasge.Sprite()
        self.alpha_sprite.loadTexture("/data/images/character_robot_idle.png")
        self.alpha_sprite.x = 332
        self.alpha_shader = self.renderer.loadPixelShader("/data/shaders/alpha.frag")
        self.uniform = self.alpha_shader.uniform("alpha")
        print(self.uniform.value)

        self.red_sprite = pyasge.Sprite()
        self.red_sprite.loadTexture("/data/images/character_robot_idle.png")
        self.red_sprite.x = 332 * 2
        self.red_shader = self.renderer.loadPixelShader("/data/shaders/red.frag")
        self.red_sprite.shader = self.red_shader

    def update(self, game_time) -> None:
        pass

    def render(self, game_time) -> None:
        self.renderer.shader = None
        self.renderer.render(self.sprite)
        self.alpha_shader.uniform("alpha").set(0.1)
        self.renderer.shader = self.alpha_shader
        self.renderer.render(self.alpha_sprite)
        self.renderer.render(self.red_sprite)


def main():
    settings = pyasge.GameSettings()
    settings.window_width = 1024
    settings.window_height = 768
    settings.vsync = pyasge.Vsync.DISABLED
    game = MyASGEGame(settings)
    game.run()


if __name__ == "__main__":
    main()
