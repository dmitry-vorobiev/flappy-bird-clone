#pragma once

#include <vector>

#include "../ext_deps.h"
#include "../errors.h"

struct LayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int size(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return sizeof(GLfloat);
			case GL_UNSIGNED_INT:	return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:	return sizeof(GLbyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<LayoutElement> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout()
		: m_stride(0) 
	{}

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * LayoutElement::size(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * LayoutElement::size(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * LayoutElement::size(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<LayoutElement> elements() const { return m_elements; }
	inline unsigned int stride() const { return m_stride; }
};
