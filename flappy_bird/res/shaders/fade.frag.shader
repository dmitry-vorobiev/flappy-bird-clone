#version 330 core

layout(location = 0) out vec4 out_color;

uniform float u_time;

void main()
{
	out_color = vec4(1.0, 1.0, 1.0, 1.0 - u_time);
}