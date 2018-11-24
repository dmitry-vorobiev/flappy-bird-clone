#version 330 core

layout(location = 0) out vec4 out_color;

in DATA
{
	vec2 texCoords;
} fs_in;

uniform int u_top;
uniform sampler2D u_texture;

void main()
{

	if (u_top == 1)
		out_color = texture(u_texture, vec2(fs_in.texCoords.x, 1.0f - fs_in.texCoords.y));
	else
		out_color = texture(u_texture, fs_in.texCoords);

	if (out_color.w < 1.0f)
		discard;
}