#pragma once

#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/vertex_array.h"

#include "glm/glm.hpp"

class Cat
{
public:
	static const float WIDTH, HEIGHT, GRAVITY;

private:
	float m_alive;
	float m_angle, m_dy;
	glm::vec3 m_position;
	VertexArray m_mesh;
	Texture m_texture;
	Shader m_shader;
	
public:
	Cat();

	inline bool isAlive() const { return m_alive; }
	inline float y() const { return m_position.y; }

	void update();
	void render();
	void reset();
	inline void die() { m_alive = false; };
};
