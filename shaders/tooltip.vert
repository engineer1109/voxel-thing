#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 Color;

uniform vec3 color;

uniform mat4 pvm;

void main() {
    gl_Position = pvm * vec4(aPos, 1.0);
    Color = color;
}
