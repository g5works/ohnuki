#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texcoord;

uniform mat4 transform;

out vec3 fragcolor;
out vec2 frag_texture_coords;

void main() {

    gl_Position = position*transform;

    fragcolor = color;
    frag_texture_coords = texcoord;

}