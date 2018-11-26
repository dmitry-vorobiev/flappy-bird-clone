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

const float Level::PIPE_GAP = 12.0f;

Level::Level() :
	m_catAlive(true),
	m_xScroll(0),
	m_map(0),
	m_pipe_index(0),
	m_background(true, 6),
	m_texture("res/images/bg.jpeg"),
	m_shader("res/shaders/bg.vert.shader", "res/shaders/bg.frag.shader"),
	m_cat(),
	m_pipes{ Pipe(0.0f, 0.0f), m_pipes[0], m_pipes[0], m_pipes[0], m_pipes[0], m_pipes[0], m_pipes[0], m_pipes[0], m_pipes[0], m_pipes[0] }
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
	if (m_catAlive)
	{
		m_xScroll--;

		if (-m_xScroll % 335 == 0)
			m_map++;

		if (-m_xScroll > 250 && -m_xScroll % 120 == 0)
			updatePipes();
	}

	m_cat.update();

	if (m_catAlive && collision())
	{
		m_catAlive = false;
		m_cat.fall();
	}
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
		m_background.draw();
	}

	renderPipes();
	m_cat.render();
}

void Level::createPipes()
{
	Pipe::init();

	while (m_pipe_index < 5 * 2)
	{
		updatePipes();
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

	VertexArray& mesh = Pipe::mesh();
	mesh.bind();

	for (int i = 0; i < 5 * 2; i++)
	{
		shader.setUniformMat4f("u_modelMatrix", m_pipes[i].modelMatrix());
		shader.setUniform1i("u_top", i % 2 == 0 ? 1 : 0);
		mesh.draw();
	}
}

bool Level::collision()
{
	for (int i = 0; i < 5 * 2; i++)
	{
		float catX = -m_xScroll * 0.05f;
		float catY = m_cat.y();

		float halfSize = Cat::SIZE / 2.0f;

		float catX0 = catX - halfSize * 2.43f;
		float catX1 = catX + halfSize;
		float catY0 = catY - halfSize;
		float catY1 = catY + halfSize;

		float pipeX0 = m_pipes[i].x();
		float pipeX1 = pipeX0 + Pipe::WIDTH;
		float pipeY0 = m_pipes[i].y();
		float pipeY1 = pipeY0 + Pipe::HEIGHT;

		if (catX1 > pipeX0 && catX0 < pipeX1 && catY1 > pipeY0 && catY0 < pipeY1)
			return true;
	}
	return false;
}
