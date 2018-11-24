#pragma once

#include "../graphics/vertex_array.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "cat.h"

class Level
{
private:
	int m_xScroll, m_map;
	VertexArray m_background;
	Texture m_texture;
	Shader m_shader;
	Cat m_cat;

public:
	Level();

	void update();
	void render();
};