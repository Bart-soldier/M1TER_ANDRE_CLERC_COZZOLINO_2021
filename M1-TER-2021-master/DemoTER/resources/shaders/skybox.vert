#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 V;
uniform mat4 P;

out vec3 direction;

void main(void) {
    direction = a_position;
    gl_Position = vec4(P * vec4(mat3(V) * direction, 1.)).xyzz;
}
