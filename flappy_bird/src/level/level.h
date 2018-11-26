#pragma once

#include "cat.h"
#include "pipe.h"
#include "../graphics/vertex_array.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"

#include <array>
#include <vector>

class Level
{
private:
	static const float PIPE_INIT_OFFSET;
	static const float PIPE_GAP;

	bool m_catAlive;
	int m_xScroll, m_map;
	unsigned int m_pipe_index;
	VertexArray m_background;
	Texture m_texture;
	Shader m_shader;
	Cat m_cat;
	std::array<Pipe, 10> m_pipes;

public:
	Level();
	~Level();

	void update();
	void render();

private:
	void createPipes();
	void updatePipes();
	void renderPipes();

	bool collision();
};