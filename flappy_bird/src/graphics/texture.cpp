#include "texture.h"
#include "../ext_deps.h"
#include "../errors.h"

#include "nothings/stb/stb_image.h"

Texture::Texture(const std::string& path)
	: m_rendererID(0), m_buffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
	load(path);
}

Texture::~Texture()
{
	DEBUG(glDeleteTextures(1, &m_rendererID));
}

void Texture::bind(unsigned int slot) const
{
	DEBUG(glActiveTexture(GL_TEXTURE0 + slot));
	DEBUG(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::unbind() const
{
	DEBUG(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::load(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);

	DEBUG(glGenTextures(1, &m_rendererID));
	DEBUG(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	DEBUG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	DEBUG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	DEBUG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	DEBUG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	DEBUG(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, 
		GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));

	DEBUG(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_buffer)
	{
		stbi_image_free(m_buffer);
	}
}
