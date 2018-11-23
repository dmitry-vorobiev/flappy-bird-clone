#pragma once

#include "../graphics/vertex_array.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"

class Level
{
private:
	VertexArray m_background;
	Shader m_shader;
	Texture m_texture;
	int m_xScroll, m_map;

public:
	Level();
	~Level();

	void update();
	void render();
};