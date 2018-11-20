#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader
{
private:
	unsigned int m_ID;
	std::unordered_map<std::string, int> m_uniform_locations;

public:
	Shader(const std::string& vertSrcPath, const std::string& fragSrcPath);
	~Shader();

	void bind() const;
	void unbind() const;

	void set_uniform_1i(const std::string& name, int value);
	void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3);
	void set_uniform_mat4f(const std::string& name, const glm::mat4& matrix);

private:
	int uniform_loc(const std::string& name);
};