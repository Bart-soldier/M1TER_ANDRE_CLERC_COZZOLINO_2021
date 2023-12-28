#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 PV;
uniform mat4 M;

void main() {
    gl_Position = PV * M * vec4(a_position, 1.);
}
