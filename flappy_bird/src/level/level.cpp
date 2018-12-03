#include "level.h"
#include "pipe.h"
#include "../errors.h"
#include "../global.h"
#include "../input.h"
#include "../utils/arrays.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"

#include <cstdlib>
#include <cmath>

#include "glm/glm.hpp"


Level::Level() :
	m_time(0),
	m_distance(0),
	m_pipe_index(0),
	m_background(true, 6),
	m_fadeEffect(false, 6),
	m_texture("res/images/bg.png"),
	m_bgShader("res/shaders/bg.vert.shader", "res/shaders/bg.frag.shader"),
	m_fadeShader("res/shaders/fade.vert.shader", "res/shaders/fade.frag.shader"),
	m_cat(),
	m_pipes(utils::arrays::make_array_n<10>(Pipe(0.0f, 0.0f)))
{
	constexpr float y = HALF_SCREEN_SIZE_Y;

	float vertices[] {
		-10.0f, -y,  0.0f, 1.0f,
		-10.0f,  y,  0.0f, 0.0f,
		 20.0f,  y,  1.0f, 0.0f,
		 20.0f, -y,  1.0f, 1.0f
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

	m_bgShader.bind();
	m_bgShader.setUniformMat4f("u_projMatrix", PROJECTION_MATRIX);
	m_bgShader.setUniform1i("u_texture", texSlot);

	m_fadeShader.bind();
	m_fadeShader.setUniformMat4f("u_projMatrix", PROJECTION_MATRIX);

	m_background.unbind();
	vb.unbind();
	ib.unbind();
	m_bgShader.unbind();

	createPipes();
}

Level::~Level()
{
	Pipe::destroy();
}

void Level::update()
{
	if (m_cat.alive())
	{
		m_distance++;

		if (collision())
			m_cat.die();

		if (m_distance > 250 && m_distance % 120 == 0)
			updatePipes();
	}
	else if (m_cat.y() < -HALF_SCREEN_SIZE_Y && input::isKeyDown(GLFW_KEY_SPACE))
	{
		return reset();
	}

	m_cat.update();
	m_time += 0.015f;
}

void Level::render()
{
	m_texture.bind();
	m_bgShader.bind();
	m_bgShader.setUniform2f("u_cat", 0.0f, m_cat.y());
	m_background.bind();

	for (int i = 0; i < 2; i++)
	{
		using namespace glm;

		float x = i * 30 - (m_distance % 1080) / 36.0f;
		mat4 viewMatrix = translate(mat4(1.0f), vec3(x, 0.0f, 0.0f));

		m_bgShader.setUniformMat4f("u_viewMatrix", viewMatrix);
		m_background.draw();
	}

	renderPipes();
	m_cat.render();

	if (m_time <= 1.0f)
	{
		m_fadeShader.bind();
		m_fadeShader.setUniform1f("u_time", m_time);
		m_fadeEffect.draw();
	}
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
	float y0 = PIPE_GAP * std::rand() / (RAND_MAX * 3.0f);
	float y1 = y0 - PIPE_GAP;

	m_pipes[m_pipe_index++ % 10] = Pipe(x, y0);
	m_pipes[m_pipe_index++ % 10] = Pipe(x, y1);
}

void Level::renderPipes()
{
	using namespace glm;

	Shader& shader = Pipe::shader();
	shader.bind();

	mat4 transform = translate(mat4(1.0f), vec3(m_distance * -0.05f, 0.0f, 0.0f));
	shader.setUniformMat4f("u_viewMatrix", transform);
	shader.setUniform2f("u_cat", 0.0f, m_cat.y());

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
		float catX = m_distance * 0.05f;
		float catY = m_cat.y();

		if (abs(catY) > HALF_SCREEN_SIZE_Y)
			return true;

		float catX0 = catX - Cat::WIDTH / 2.0f;
		float catX1 = catX + Cat::WIDTH / 2.0f;
		float catY0 = catY - Cat::HEIGHT / 2.0f;
		float catY1 = catY + Cat::HEIGHT / 2.0f;

		float pipeX0 = m_pipes[i].x();
		float pipeX1 = pipeX0 + Pipe::WIDTH;
		float pipeY0 = m_pipes[i].y();
		float pipeY1 = pipeY0 + Pipe::HEIGHT;

		if (catX1 > pipeX0 && catX0 < pipeX1 && catY1 > pipeY0 && catY0 < pipeY1)
			return true;
	}
	return false;
}

void Level::reset()
{
	m_time = 0.0f;
	m_distance = 0;
	m_pipe_index = 0;

	m_cat.reset();
	createPipes();
}
