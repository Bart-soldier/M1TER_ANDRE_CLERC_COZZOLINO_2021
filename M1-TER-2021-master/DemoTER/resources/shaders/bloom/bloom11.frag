#version 330 core

out vec4 FragColor;

uniform sampler2D tex;

in vec2 texCoords[11];

void main() {
	FragColor = vec4(0.0);
	FragColor += texture2D(tex, texCoords[0]) * 0.000003;
	FragColor += texture2D(tex, texCoords[1]) * 0.000229;
	FragColor += texture2D(tex, texCoords[2]) * 0.005977;
	FragColor += texture2D(tex, texCoords[3]) * 0.060598;
	FragColor += texture2D(tex, texCoords[4]) * 0.24173;
	FragColor += texture2D(tex, texCoords[5]) * 0.382925;
	FragColor += texture2D(tex, texCoords[6]) * 0.24173;
	FragColor += texture2D(tex, texCoords[7]) * 0.060598;
	FragColor += texture2D(tex, texCoords[8]) * 0.005977;
	FragColor += texture2D(tex, texCoords[9]) * 0.000229;
	FragColor += texture2D(tex, texCoords[10]) * 0.000003;
}
