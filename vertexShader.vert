#version 430

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 theColor;
out vec4 color;

void main() {
    color = theColor;
    gl_Position = vec4(position,0,1);
}