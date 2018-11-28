#version 330 core

layout(location = 0) in vec4 in_pos;
layout(location = 1) in vec2 in_texCoords;

out DATA
{
	vec2 texCoords;
	vec3 position;
} vs_out;

uniform mat4 u_projMatrix;
uniform mat4 u_viewMatrix;

void main()
{
	gl_Position = u_projMatrix * u_viewMatrix * in_pos;
	vs_out.texCoords = in_texCoords;
	vs_out.position = vec3(u_viewMatrix * in_pos);
}