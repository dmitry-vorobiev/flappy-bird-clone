#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray
{
private:
	bool m_drawElements;
	unsigned int m_rendererID, m_count;
public:
	VertexArray(bool drawElements, unsigned int count);
	~VertexArray();

	void bind() const;
	void unbind() const;

	void draw() const;

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
