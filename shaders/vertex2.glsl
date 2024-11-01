#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
out vec4 fragcolor;

uniform float xtransf;

void main() {

    gl_Position = vec4(position.x+xtransf, position.y, position.z, position.w);
    fragcolor = color;

}