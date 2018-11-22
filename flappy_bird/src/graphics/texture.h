#pragma once

#include <string>

class Texture
{
private:
	unsigned int m_rendererID;
	unsigned char* m_buffer;
	int m_width, m_height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int width() const { return m_width; }
	inline int height() const { return m_height; }

private:
	void load(const std::string& path);
};
