#version 330 core

out vec4 FragColor;

uniform sampler2D texture1;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;
in float LightStrength;

void main() {
    vec3 color = texture(texture1, TexCoord).xyz;

    FragColor = vec4(color * LightStrength, 1.0);
}
