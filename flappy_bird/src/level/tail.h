#pragma once

#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/vertex_array.h"

#include "glm/glm.hpp"

#include <array>

class Tail
{
private:
	unsigned int m_updIndex;
	std::array<float, 10> m_y;
	std::array<float, 10> m_angle;
	VertexArray m_mesh;
	Texture m_texture;
	Shader m_shader;

public:
	Tail();

	void update(float y, float angle);
	void render();
};
