#version 330 core
#define FRAG_COLOUR     0
in VertexData
{
    vec2    uvs;
    vec4    rgba;
} fs_in;

uniform sampler2D image;
layout  (location = FRAG_COLOUR, index = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, fs_in.rgba.a) * texture(image, fs_in.uvs);
}
