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
	float x = fs_in.texCoords.x;
	float y = u_top == 1 ? 1.0f - fs_in.texCoords.y : fs_in.texCoords.y;

	out_color = texture(u_texture, vec2(x, y));

	if (out_color.w < 1.0f)
		discard;
}