#include "cat.h"
#include "../errors.h"
#include "../global.h"
#include "../input.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"


const float Cat::HEIGHT = 1.0f;

const float Cat::WIDTH = 1.61904762f * Cat::HEIGHT;

Cat::Cat() :
	m_alive(true),
	m_angle(0.0f),
	m_dy(0.0f),
	m_position(0.0f, 0.0f, 0.0f),
	m_mesh(true, 6),
	m_texture("res/images/cat.png"),
	m_shader("res/shaders/cat.vert.shader", "res/shaders/cat.frag.shader")
{
	const float x = Cat::WIDTH / 2.0f;
	const float y = Cat::HEIGHT / 2.0f;
	const float z = 0.2f;

	float vertices[] {
		-x, -y,  z,		0.0f, 1.0f,
		-x,  y,  z,		0.0f, 0.0f,
		 x,  y,  z,		1.0f, 0.0f,
		 x, -y,  z,		1.0f, 1.0f
	};

	unsigned int indices[] {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vb(&vertices, 4 * 5 * sizeof(float));
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

void Cat::update()
{
	m_angle = -m_dy * 90.0f;
	m_position.y -= m_dy;

	if (!m_alive)
		m_dy = 0.15f;
	else if (input::isKeyDown(GLFW_KEY_SPACE))
		m_dy = -0.15f;
	else
		m_dy += 0.01f;
}

void Cat::fall()
{
	m_dy = 0.15f;
}

void Cat::render()
{
	using namespace glm;

	m_shader.bind();
	m_texture.bind();
	m_mesh.bind();

	mat4 transform(1.0f);
	transform = translate(transform, m_position);
	transform = rotate(transform, radians(m_angle), vec3(0.0f, 0.0f, 1.0f));
	m_shader.setUniformMat4f("u_modelMatrix", transform);
	m_mesh.draw();
}
