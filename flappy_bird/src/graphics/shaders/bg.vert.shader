#version 330 core

layout(location = 0) in vec4 in_pos;
layout(location = 1) in vec2 in_tex_coords;

uniform mat4 u_proj_matrix;

void main()
{
	gl_Position = u_proj_matrix * in_pos;
}