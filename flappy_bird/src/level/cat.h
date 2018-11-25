#pragma once

#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/vertex_array.h"

#include "glm/glm.hpp"

class Cat
{
private:
	static const float SIZE;

	float m_angle, m_dy;
	glm::vec3 m_position;
	VertexArray m_mesh;
	Texture m_texture;
	Shader m_shader;
	
public:
	Cat();

	void update();
	void render();

private:
	void fall();
};
