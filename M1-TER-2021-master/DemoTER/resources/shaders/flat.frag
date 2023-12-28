#version 330 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BloomColor;

uniform vec3 color;
uniform float exposure;

void main() {
    vec3 c = vec3(1.0) - exp(-color * exposure);
   
    FragColor = vec4(c, 1.0);
    BloomColor = FragColor;
}
