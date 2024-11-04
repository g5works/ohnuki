#version 330 core

out vec4 color;
in vec4 fragcolor;
in vec2 frag_texture_coords;

uniform sampler2D copper;
uniform sampler2D blitter;

uniform float magnitude;

void main() {

    color = mix(texture(copper, frag_texture_coords), texture(blitter, frag_texture_coords), magnitude);

}
