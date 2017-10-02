#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixRatio;

void main() {
    vec2 tex2TexCoord = vec2(-TexCoord.x, TexCoord.y);

	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, tex2TexCoord), mixRatio) * vec4(ourColor, 1);
}
