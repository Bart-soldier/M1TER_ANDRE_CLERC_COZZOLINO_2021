#version 330 core

out vec4 FragColor;

uniform sampler2D tex;

in vec2 uv;

void main() {
	FragColor += texture2D(tex, uv);
}
