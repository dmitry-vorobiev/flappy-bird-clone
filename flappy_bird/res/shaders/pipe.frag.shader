#version 330 core

layout(location = 0) out vec4 out_color;

in DATA
{
	vec2 texCoords;
	vec3 position;
} fs_in;

uniform int u_top;

uniform vec2 u_cat;

uniform sampler2D u_texture;

void main()
{
	float x = fs_in.texCoords.x;
	float y = u_top == 1 ? 1.0f - fs_in.texCoords.y : fs_in.texCoords.y;

	out_color = texture(u_texture, vec2(x, y));

	if (out_color.w < 1.0f)
		discard;

	out_color *= 2.0 / (length(u_cat - fs_in.position.xy) + 1.5) + 0.6;
	out_color.w = 1.0;
}