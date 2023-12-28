#version 330 core

out vec4 FragColor;

uniform sampler2D tex;

in vec2 texCoords[5];

void main() {
	FragColor = vec4(0.0);
	FragColor += texture2D(tex, texCoords[0]) * 0.06136;
	FragColor += texture2D(tex, texCoords[1]) * 0.24477;
	FragColor += texture2D(tex, texCoords[2]) * 0.38774;
	FragColor += texture2D(tex, texCoords[3]) * 0.24477;
	FragColor += texture2D(tex, texCoords[4]) * 0.06136;
}
