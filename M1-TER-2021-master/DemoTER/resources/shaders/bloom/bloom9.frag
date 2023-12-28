#version 330 core

out vec4 FragColor;

uniform sampler2D tex;

in vec2 texCoords[9];

void main() {
	FragColor = vec4(0.0);
	FragColor += texture2D(tex, texCoords[0]) * 0.000229;
	FragColor += texture2D(tex, texCoords[1]) * 0.005977;
	FragColor += texture2D(tex, texCoords[2]) * 0.060598;
	FragColor += texture2D(tex, texCoords[3]) * 0.241732;
	FragColor += texture2D(tex, texCoords[4]) * 0.382928;
	FragColor += texture2D(tex, texCoords[5]) * 0.241732;
	FragColor += texture2D(tex, texCoords[6]) * 0.060598;
	FragColor += texture2D(tex, texCoords[7]) * 0.005977;
	FragColor += texture2D(tex, texCoords[8]) * 0.000229;
}
