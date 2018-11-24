#include "pipe.h"
#include "../errors.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"

#include "glm/gtc/matrix_transform.hpp"


float Pipe::s_width = 1.5f;

float Pipe::s_height = 8.0f;


VertexArray* Pipe::s_mesh(nullptr);

Texture* Pipe::s_texture(nullptr);

Shader* Pipe::s_shader(nullptr);

Pipe::Pipe(float x, float y) :
	m_position(x, y, 0.0f),
	m_modelMatrix(glm::translate(glm::mat4(1.0f), m_position))
{
}

VertexArray& Pipe::mesh()
{
	return *s_mesh;
}

Texture& Pipe::texture()
{
	return *s_texture;
}

Shader& Pipe::shader()
{
	return *s_shader;
}

void Pipe::init()
{
	const float z = 0.1f;

	float vertices[]{
		   0.0f,     0.0f,  z,  0.0f, 1.0f,
		   0.0f, s_height,  z,  0.0f, 0.0f,
		s_width, s_height,  z,  1.0f, 0.0f,
		s_width,     0.0f,  z,  1.0f, 1.0f
	};

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0
	};

	s_mesh = new VertexArray();
	s_texture = new Texture("res/images/pipe.png");
	s_shader = new Shader(
		"res/shaders/pipe.vert.shader",
		"res/shaders/pipe.frag.shader"
	);

	VertexBuffer vb(&vertices, 4 * 5 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);

	VertexArray& mesh = *s_mesh;
	mesh.addBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	unsigned int texSlot = 0;
	Texture& texture = *s_texture;
	texture.bind(texSlot);

	glm::mat4 projMatrix = glm::ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f);

	Shader& shader = *s_shader;
	shader.bind();
	shader.setUniformMat4f("u_projMatrix", projMatrix);
	shader.setUniform1i("u_texture", texSlot);

	mesh.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();
}

void Pipe::destroy()
{
	delete s_mesh;
	delete s_texture;
	delete s_shader;
}
