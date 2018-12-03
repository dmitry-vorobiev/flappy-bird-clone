#pragma once

#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/vertex_array.h"

#include "glm/glm.hpp"

#include <array>

class Tail
{
private:
	static constexpr char ELEMENTS = 60;

	unsigned int m_updIndex;
	std::array<float, ELEMENTS> m_y;
	std::array<float, ELEMENTS> m_angle;
	VertexArray m_mesh;
	Texture m_texture;
	Shader m_shader;

public:
	Tail();

	void update(float y, float angle);
	void render();
};
