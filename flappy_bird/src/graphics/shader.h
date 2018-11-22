#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader
{
private:
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_uniformLocations;

public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform1i(const std::string& name, int value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	int uniformLoc(const std::string& name);
};