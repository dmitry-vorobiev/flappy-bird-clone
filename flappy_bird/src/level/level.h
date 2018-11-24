#pragma once

#include "cat.h"
#include "pipe.h"
#include "../graphics/vertex_array.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"

#include <vector>

class Level
{
private:
	static float s_offset;

	int m_xScroll, m_map;
	VertexArray m_background;
	Texture m_texture;
	Shader m_shader;
	Cat m_cat;
	std::vector<Pipe> m_pipes;

public:
	Level();
	~Level();

	void update();
	void render();

private:
	void createPipes();
	void updatePipes();
	void renderPipes();
};