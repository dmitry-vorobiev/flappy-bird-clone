#include "../ext_deps.h"
#include "../errors.h"
#include "index_buffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	DEBUG(glGenBuffers(1, &m_rendererID));
	DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	DEBUG(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	DEBUG(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::bind() const
{
	DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::unbind() const
{
	DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}