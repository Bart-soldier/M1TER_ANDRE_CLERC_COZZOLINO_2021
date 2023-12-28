#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec3 a_tangent;
layout(location = 3) in vec2 a_uv;

out vec3 worldPos;
out vec3 normal;
out vec3 tangent;
out vec2 uv;

uniform mat4 PV;
uniform mat4 M;

void main() {
    vec4 W = M * vec4(a_position, 1.);

    worldPos = W.xyz;
    normal = mat3(M) * a_normal;
    tangent = mat3(M) * a_tangent;
    uv = a_uv;

    gl_Position = PV * W;
}
