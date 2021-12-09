#version 450 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vCol;
layout (location = 2) in vec2 vTex;
layout (location = 3) in mat4 mIns;

out vec4 vertex_color;
out vec2 vertex_texture;

uniform mat4 transformations;

void main()
{
    vertex_color = vec4(vCol, 1);
    vertex_texture = vTex;
    gl_Position = transformations * vec4(vPos, 1.0);
}
