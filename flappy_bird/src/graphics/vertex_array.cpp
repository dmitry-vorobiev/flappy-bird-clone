#include "vertex_array.h"
#include "../ext_deps.h"
#include "../errors.h"

VertexArray::VertexArray()
	:m_rendererID(0)
{
	DEBUG(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
	DEBUG(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::bind() const
{
	DEBUG(glBindVertexArray(m_rendererID));
}

void VertexArray::unbind() const
{
	DEBUG(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.elements();

	for (unsigned int i = 0, offset = 0; i < elements.size(); i++)
	{
		const auto& el = elements[i];
		DEBUG(glEnableVertexAttribArray(i));
		DEBUG(glVertexAttribPointer(i, el.count, el.type, el.normalized, layout.stride(), (const void*)offset));
		offset += el.count * LayoutElement::size(el.type);
	}

}
