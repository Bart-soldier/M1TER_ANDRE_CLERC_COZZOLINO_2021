#version 330 core

out vec4 FragColor;

uniform sampler2D base;
uniform sampler2D bloom;

uniform float gamma;
uniform bool showBloom;

in vec2 texCoord;

void main() {
	vec3 color;

	if(showBloom) color = texture(bloom, texCoord).rgb;
	else color = texture(base, texCoord).rgb + texture(bloom, texCoord).rgb;

	color = pow(color, vec3(1.0 / gamma));
   
    FragColor = vec4(color, 1.0);
}
