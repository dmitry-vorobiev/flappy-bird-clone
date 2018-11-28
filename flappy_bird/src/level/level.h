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

	float m_time;
	int m_xScroll, m_map;
	unsigned int m_pipe_index;
	VertexArray m_background, m_fadeEffect;
	Texture m_texture;
	Shader m_bgShader, m_fadeShader;
	Cat m_cat;
	std::array<Pipe, 10> m_pipes;

public:
	Level();
	~Level();

	void update();
	void render();
	void reset();

private:
	void createPipes();
	void updatePipes();
	void renderPipes();
	bool collision();
};