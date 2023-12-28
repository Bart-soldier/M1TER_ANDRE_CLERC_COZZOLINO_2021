#version 330 core

uniform samplerCube cubemapTexture;

in vec3 direction;

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BloomColor;

uniform float exposure;
uniform float gamma;

void main(void) {
    vec3 color = texture(cubemapTexture, direction).rgb;
    color = vec3(1.0) - exp(-color * exposure);
    //color = pow(color, vec3(1.0 / gamma));  fait dans "merge""
    FragColor = vec4(color, 1.0);
    BloomColor = vec4(0.0);
}
