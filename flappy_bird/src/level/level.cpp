#include "level.h"
#include "pipe.h"
#include "../errors.h"
#include "../global.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"

#include <cstdlib>

#include "glm/glm.hpp"

const float Level::PIPE_INIT_OFFSET = 5.0f;

const float Level::PIPE_GAP = 11.5f;

Level::Level() :
	m_xScroll(0),
	m_map(0),
	m_pipe_index(0),
	m_background(),
	m_texture("res/images/bg.jpeg"),
	m_shader("res/shaders/bg.vert.shader", "res/shaders/bg.frag.shader"),
	m_cat(),
	m_pipes()
{
	constexpr float y = 10.0f * 9.0f / 16.0f;

	float vertices[] {
		-10.0f, -y,  0.0f, 1.0f,
		-10.0f,  y,  0.0f, 0.0f,
		 0.0f,   y,  1.0f, 0.0f,
		 0.0f,  -y,  1.0f, 1.0f
	};

	unsigned int indices[] {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vb(&vertices, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);

	m_background.addBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	unsigned int texSlot = 0;
	m_texture.bind(texSlot);

	m_shader.bind();
	m_shader.setUniformMat4f("u_projMatrix", PROJECTION_MATRIX);
	m_shader.setUniform1i("u_texture", texSlot);

	m_background.unbind();
	vb.unbind();
	ib.unbind();
	m_shader.unbind();

	createPipes();
}

Level::~Level()
{
	Pipe::destroy();
}

void Level::update()
{
	m_xScroll--;

	if (-m_xScroll % 335 == 0)
		m_map++;

	if (-m_xScroll > 250 && -m_xScroll % 120 == 0)
		updatePipes();

	m_cat.update();
}

void Level::render()
{
	m_texture.bind();
	m_shader.bind();
	m_background.bind();

	for (auto i = m_map; i < m_map + 4; i++)
	{
		using namespace glm;

		float x = i * 10 + m_xScroll * 0.03f;
		mat4 viewMatrix = translate(mat4(1.0f), vec3(x, 0.0f, 0.0f));
		m_shader.setUniformMat4f("u_viewMatrix", viewMatrix);

		DEBUG(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
	}

	renderPipes();
	m_cat.render();
}

void Level::createPipes()
{
	Pipe::init();

	for (; m_pipe_index < 5 * 2; m_pipe_index += 2)
	{
		float x = PIPE_INIT_OFFSET + m_pipe_index * 3.0f;
		float y = 4.0f * std::rand() / RAND_MAX;

		Pipe top(x, y);
		Pipe bottom(x, y - PIPE_GAP);

		m_pipes.reserve(10);
		m_pipes.push_back(top);
		m_pipes.push_back(bottom);
	}
}

void Level::updatePipes()
{
	float x = PIPE_INIT_OFFSET + m_pipe_index * 3.0f;
	float y = 4.0f * std::rand() / RAND_MAX;

	m_pipes[m_pipe_index++ % 10] = Pipe(x, y);
	m_pipes[m_pipe_index++ % 10] = Pipe(x, y - PIPE_GAP);
}

void Level::renderPipes()
{
	using namespace glm;

	Shader& shader = Pipe::shader();
	shader.bind();

	mat4 transform = translate(mat4(1.0f), vec3(m_xScroll * 0.05f, 0.0f, 0.0f));
	shader.setUniformMat4f("u_viewMatrix", transform);

	Pipe::texture().bind();
	Pipe::mesh().bind();

	for (int i = 0; i < 5 * 2; i++)
	{
		shader.setUniformMat4f("u_modelMatrix", m_pipes[i].modelMatrix());
		shader.setUniform1i("u_top", i % 2 == 0 ? 1 : 0);

		DEBUG(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
	}
}
