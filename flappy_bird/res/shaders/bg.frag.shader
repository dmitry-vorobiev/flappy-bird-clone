#version 330 core

layout(location = 0) out vec4 out_color;

in DATA
{
	vec2 texCoords;
	vec3 position;
} fs_in;

uniform vec2 u_cat;

uniform sampler2D u_texture;

void main()
{
	out_color = texture(u_texture, fs_in.texCoords);
	// out_color *= 2.0 / (length(u_cat - fs_in.position.xy) + 2.5) + 0.7;
}