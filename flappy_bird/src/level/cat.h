#pragma once

#include "tail.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/vertex_array.h"

#include "glm/glm.hpp"

#include <array>

class Cat
{
public:
	static constexpr char FRAMES = 12;
	static constexpr char FRAME_DELAY = 5;
	static constexpr float HEIGHT = 1.0f;
	static constexpr float WIDTH = 1.61904762f * Cat::HEIGHT;
	static constexpr float GRAVITY = 0.006f;

private:
	bool m_alive;
	char m_frame;
	char m_frameTime;
	float m_angle, m_dy;
	glm::vec3 m_position;
	VertexArray m_mesh;
	std::array<Texture, FRAMES> m_textures;
	Shader m_shader;
	Tail m_tail;
	
public:
	Cat();

	inline bool alive() const { return m_alive; }
	inline float y() const { return m_position.y; }

	void update();
	void render();
	void reset();
	inline void die() { m_alive = false; };
};
