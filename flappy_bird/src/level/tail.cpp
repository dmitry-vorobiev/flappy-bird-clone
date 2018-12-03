#include "tail.h"
#include "cat.h"

#include "../errors.h"
#include "../global.h"
#include "../input.h"
#include "../utils/arrays.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"

Tail::Tail() :
	m_mesh(true, 6),
	m_texture("res/images/tail.png"),
	m_shader("res/shaders/tail.vert.shader", "res/shaders/tail.frag.shader"),
	m_y(utils::arrays::make_array_n<10>(0.0f)),
	m_angle(utils::arrays::make_array_n<10>(0.0f))
{
	constexpr float y = Cat::HEIGHT / 3.0f;
	constexpr float z = 0.15f;

	float verticies[]{
		-0.12f, -y, z,	0.0f, 1.0f,
		-0.12f,  y, z,	0.0f, 0.0f,
		 0.12f,  y, z,	1.0f, 0.0f,
		 0.12f, -y, z,	1.0f, 1.0f
	};

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vb(&verticies, 4 * 5 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);

	m_mesh.addBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	unsigned int texSlot = 0;
	m_texture.bind(texSlot);

	m_shader.bind();
	m_shader.setUniformMat4f("u_projMatrix", PROJECTION_MATRIX);
	m_shader.setUniform1i("u_texture", texSlot);

	m_mesh.unbind();
	vb.unbind();
	ib.unbind();
	m_shader.unbind();
}

void Tail::update(float y, float angle)
{
	for (int i = 0; i < 9; i++)
	{
		m_y[i] = m_y[i + 1];
		m_angle[i] = m_angle[i + 1];
	}
	m_y[9] = y;
	m_angle[9] = angle;
}

void Tail::render()
{
	using namespace glm;

	m_mesh.bind();
	m_texture.bind();
	m_shader.bind();

	for (int i = 0; i < 10; i++)
	{
		mat4 transform(1.0f);
		transform = translate(transform, vec3(-Cat::WIDTH / 2.8f - 0.2f * i, m_y[9 - i], 0.0f));
		transform = rotate(transform, radians(m_angle[9 - i]), vec3(0.0f, 0.0f, 1.0f));
		m_shader.setUniformMat4f("u_modelMatrix", transform);
		m_mesh.draw();
	}
}