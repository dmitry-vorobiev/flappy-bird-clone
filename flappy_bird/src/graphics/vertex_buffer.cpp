#include "../errors.h"
#include "../ext_deps.h"
#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	DEBUG(glGenBuffers(1, &m_rendererID));
	DEBUG(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	DEBUG(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	DEBUG(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::bind() const
{
	DEBUG(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::unbind() const
{
	DEBUG(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
