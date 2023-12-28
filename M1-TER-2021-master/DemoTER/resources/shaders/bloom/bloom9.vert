#version 330 core
layout (location = 0) in vec3 aPos;

uniform float size;
uniform bool horizontal;

out vec2 texCoords[9];

void main() {
	gl_Position = vec4(aPos, 1.0);
	vec2 actualCoord = aPos.xy * 0.5 + 0.5;
	float pxSize = 1.0 / size;

	if(horizontal) {
		for(int i = 0; i < 9; ++i) {
			float dec = float(i - 4);
			texCoords[i] = actualCoord + vec2(pxSize * dec, 0.0);
		}
	} else {
		for(int i = 0; i < 9; ++i) {
			float dec = float(i - 4);
			texCoords[i] = actualCoord + vec2(0.0, pxSize * dec);
		}
	}
}
