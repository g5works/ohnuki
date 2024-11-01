#version 330 core

out vec4 color;
in vec4 fragcolor;

uniform vec4 uni_icolor;

void main() {

    color = uni_icolor;

}