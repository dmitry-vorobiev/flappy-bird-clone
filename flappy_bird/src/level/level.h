#pragma once

#include "../graphics/vertex_array.h"
#include "../shader.h"

class Level
{
private:
	VertexArray m_background;
	Shader m_shader;

public:
	Level();
	~Level();

	void init();
	void render();
};