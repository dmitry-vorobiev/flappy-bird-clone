#version 330 core

layout(location = 0) out vec4 out_color;

in DATA
{
	vec2 texCoords;
} fs_in;

uniform sampler2D u_texture;

void main()
{
	out_color = texture(u_texture, fs_in.texCoords);
	out_color.w = 0.6;
}