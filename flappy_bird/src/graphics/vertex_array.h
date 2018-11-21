#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray
{
private:
	unsigned int m_rendererID;
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void init();
	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
