#include "pipe.h"
#include "../errors.h"
#include "../global.h"
#include "../graphics/index_buffer.h"
#include "../graphics/vertex_buffer.h"
#include "../graphics/vertex_buffer_layout.h"

const glm::mat4 IDENTITY(1.0f);

const float Pipe::WIDTH = 1.5f;

const float Pipe::HEIGHT = 8.0f;

PipeAssets* Pipe::s_assets(nullptr);

Pipe::Pipe(float x, float y) :
	m_position(x, y, 0.0f),
	m_modelMatrix(glm::translate(IDENTITY, m_position))
{
}

void Pipe::init()
{
	const float z = 0.1f;

	float vertices[]{
		 0.0f,   0.0f, z, 0.0f, 1.0f,
		 0.0f, HEIGHT, z, 0.0f, 0.0f,
		WIDTH, HEIGHT, z, 1.0f, 0.0f,
		WIDTH,   0.0f, z, 1.0f, 1.0f
	};

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0
	};

	s_assets = new PipeAssets{
		VertexArray(true, 6),
		Texture("res/images/pipe.png"),
		Shader("res/shaders/pipe.vert.shader", "res/shaders/pipe.frag.shader")
	};

	VertexBuffer vb(&vertices, 4 * 5 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);

	VertexArray& mesh = Pipe::mesh();
	mesh.addBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	unsigned int texSlot = 0;
	Texture& texture = Pipe::texture();
	texture.bind(texSlot);

	Shader& shader = Pipe::shader();
	shader.bind();
	shader.setUniformMat4f("u_projMatrix", PROJECTION_MATRIX);
	shader.setUniform1i("u_texture", texSlot);

	mesh.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();
}

void Pipe::destroy()
{
	delete s_assets;
}
