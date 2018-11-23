#version 330 core

layout(location = 0) in vec4 in_pos;
layout(location = 1) in vec2 in_texCoords;

uniform mat4 u_projMatrix;

void main()
{
	gl_Position = u_projMatrix * in_pos;
}