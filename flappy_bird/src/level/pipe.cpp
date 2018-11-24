#include "pipe.h"
#include "../errors.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"

#include "glm/gtc/matrix_transform.hpp"


float Pipe::s_width = 1.5f;

float Pipe::s_height = 8.0f;


Pipe::Pipe(float x, float y) :
	m_position(x, y, 0.0f),
	m_modelMatrix(glm::translate(glm::mat4(1.0f), m_position))
{
}

VertexArray& Pipe::mesh()
{
	static VertexArray s_mesh;
	return s_mesh;
}

Texture& Pipe::texture()
{
	static Texture s_texture("res/images/pipe.png");
	return s_texture;
}

Shader& Pipe::shader()
{
	static Shader s_shader(
		"res/shaders/pipe.vert.shader",
		"res/shaders/pipe.frag.shader"
	);
	return s_shader;
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

	VertexArray& s_mesh = mesh();
	Texture& s_texture = texture();
	Shader& s_shader = shader();

	VertexBuffer vb(&vertices, 4 * 5 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);

	s_mesh.addBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	unsigned int texSlot = 0;
	s_texture.bind(texSlot);

	glm::mat4 projMatrix = glm::ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f);

	s_shader.bind();
	s_shader.setUniformMat4f("u_projMatrix", projMatrix);
	s_shader.setUniform1i("u_texture", texSlot);

	s_mesh.unbind();
	vb.unbind();
	ib.unbind();
	s_shader.unbind();
}

void Pipe::destroy()
{
	mesh().~VertexArray();
	texture().~Texture();
	shader().~Shader();
}
