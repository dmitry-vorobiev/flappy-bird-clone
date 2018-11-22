#include "level.h"
#include "../errors.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Level::Level()
	:m_background(), 
	m_shader(
		"src/graphics/shaders/bg.vert.shader", 
		"src/graphics/shaders/bg.frag.shader")
{
	constexpr float y = 10.0f * 9.0f / 16.0f;

	float vertices[] {
		-10.0f, -y,  0.0f,
		-10.0f,  y,  0.0f,
		 0.0f,   y,  0.0f,
		 0.0f,  -y,  0.0f
	};

	float tex_coords[] {
		0, 1,
		0, 0,
		1, 0,
		1, 1
	};

	unsigned int indices[] {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vb(&vertices, 4 * 3 * sizeof(float));
	VertexBufferLayout vb_layout;
	vb_layout.push<float>(3);
	m_background.addBuffer(vb, vb_layout);

	VertexBuffer tc(&tex_coords, 4 * 2 * sizeof(float));
	VertexBufferLayout tc_layout;
	tc_layout.push<float>(2);
	m_background.addBuffer(tc, tc_layout);

	IndexBuffer ib(indices, 6);

	glm::mat4 proj_matrix = glm::ortho(-10.0f, 10.0f, -y, y, -1.0f, 1.0f);

	m_shader.bind();
	m_shader.set_uniform_mat4f("u_proj_matrix", proj_matrix);

	m_background.unbind();
	vb.unbind();
	tc.unbind();
	ib.unbind();
	m_shader.unbind();
}

Level::~Level() {}

void Level::init()
{
}

void Level::render()
{
	m_background.bind();
	m_shader.bind();
	DEBUG(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
	m_background.unbind();
	m_shader.unbind();
}
