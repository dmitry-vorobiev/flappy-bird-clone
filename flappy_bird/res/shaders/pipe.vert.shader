#version 330 core

layout(location = 0) in vec4 in_pos;
layout(location = 1) in vec2 in_texCoords;

out DATA
{
	vec2 texCoords;
} vs_out;

uniform mat4 u_projMatrix;
uniform mat4 u_viewMatrix = mat4(1.0);
uniform mat4 u_modelMatrix = mat4(1.0);

void main()
{
	gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * in_pos;
	vs_out.texCoords = in_texCoords;
}