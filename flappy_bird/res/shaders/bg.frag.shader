#version 330 core

layout(location = 0) out vec4 out_color;

in DATA
{
	vec2 texCoords;
} fs_in;

uniform sampler2D tex;

void main()
{
	out_color = texture(tex, fs_in.texCoords);
}