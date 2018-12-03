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
	m_updIndex(0),
	m_y(utils::arrays::make_array_n<ELEMENTS>(0.0f)),
	m_angle(utils::arrays::make_array_n<ELEMENTS>(0.0f)),
	m_mesh(true, 6),
	m_texture("res/images/tail.png"),
	m_shader("res/shaders/tail.vert.shader", "res/shaders/tail.frag.shader")
{
	constexpr float x = 0.05;
	constexpr float y = Cat::HEIGHT / 3.0f;
	constexpr float z = 0.15f;

	float verticies[]{
		-x, -y,  z,	 0.0f, 1.0f,
		-x,  y,  z,	 0.0f, 0.0f,
		 x,  y,  z,	 1.0f, 0.0f,
		 x, -y,  z,	 1.0f, 1.0f
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
	m_updIndex = (m_updIndex + 1) % ELEMENTS;
	m_y[m_updIndex] = y;
	m_angle[m_updIndex] = angle;
}

void Tail::render()
{
	using namespace glm;

	m_mesh.bind();
	m_texture.bind();
	m_shader.bind();

	for (auto i = 0; i < ELEMENTS; i++)
	{
		auto index = (m_updIndex + (ELEMENTS - i)) % ELEMENTS;

		mat4 transform(1.0f);
		transform = translate(transform, vec3(-Cat::WIDTH / 3.2f - 0.08f * i, m_y[index], 0.0f));
		transform = rotate(transform, radians(m_angle[index]), vec3(0.0f, 0.0f, 1.0f));
		m_shader.setUniformMat4f("u_modelMatrix", transform);
		m_mesh.draw();
	}
}