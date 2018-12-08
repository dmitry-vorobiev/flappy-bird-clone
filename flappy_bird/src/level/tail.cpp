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
	m_chunks(utils::arrays::make_array_n<ELEMENTS>(Chunk{ 0.0f, 0.0f })),
	m_mesh(true, 6),
	m_texture("res/images/tail.png"),
	m_shader("res/shaders/tail.vert.shader", "res/shaders/tail.frag.shader")
{
	constexpr float x = 0.08f;
	constexpr float y = Cat::HEIGHT * 0.3f;
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
	m_chunks[m_updIndex] = Chunk{ y, angle };
}

void Tail::render()
{
	m_mesh.bind();
	m_texture.bind();
	m_shader.bind();

	using namespace glm;
	mat4 init = translate(mat4(1.0f), vec3(-Cat::WIDTH * 0.3f, 0.0f, 0.0f));

	for (auto i = 0; i < ELEMENTS; i++)
	{
		/* This index is used to traverse chunks in a reverse historical order 
		   (from the most recent records to the oldest ones.*/
		auto j = (m_updIndex + (ELEMENTS - i)) % ELEMENTS;

		Chunk& chunk = m_chunks[j];
		float angle = radians(chunk.angle);

		mat4 transform = translate(init, vec3(-0.08f * i, chunk.y, 0.0f));
		transform = rotate(transform, angle, Z_AXIS);
		transform = scale(transform, vec3(1.0f - sin(angle), cos(angle), 1.0f));

		m_shader.setUniformMat4f("u_modelMatrix", transform);
		m_shader.setUniform1f("u_alpha", (ELEMENTS - i * 1.0f) / ELEMENTS);
		m_mesh.draw();
	}
}

void Tail::reset()
{
	m_updIndex = 0;
	m_chunks = utils::arrays::make_array_n<ELEMENTS>(Chunk{ 0.0f, 0.0f });
}