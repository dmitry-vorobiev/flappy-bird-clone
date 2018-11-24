#include "level.h"
#include "../errors.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Level::Level() :
	m_xScroll(0),
	m_map(0),
	m_background(),
	m_texture("res/images/bg.jpeg"),
	m_shader("res/shaders/bg.vert.shader", "res/shaders/bg.frag.shader"),
	m_cat()
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

	glm::mat4 projMatrix = glm::ortho(-10.0f, 10.0f, -y, y, -1.0f, 1.0f);

	m_shader.bind();
	m_shader.setUniformMat4f("u_projMatrix", projMatrix);
	m_shader.setUniform1i("u_texture", texSlot);

	m_background.unbind();
	vb.unbind();
	ib.unbind();
	m_shader.unbind();
}

void Level::update()
{
	m_xScroll--;

	if (-m_xScroll % 335 == 0)
		m_map++;

	m_cat.update();
}

void Level::render()
{
	m_texture.bind();
	m_background.bind();
	m_shader.bind();

	for (auto i = m_map; i < m_map + 4; i++)
	{
		using namespace glm;

		float xOffset = i * 10 + m_xScroll * 0.03f;
		mat4 viewMatrix = translate(mat4(1.0f), vec3(xOffset, 0.0f, 0.0f));
		m_shader.setUniformMat4f("u_viewMatrix", viewMatrix);

		DEBUG(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
	}
	m_shader.unbind();
	m_cat.render();
}
