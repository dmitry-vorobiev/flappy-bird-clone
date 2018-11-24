#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "../ext_deps.h"
#include "../errors.h"
#include "../utils/shaders.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(
	const std::string& vertPath, 
	const std::string& fragPath
) : m_rendererID(0)
{
	m_rendererID = utils::shaders::build(vertPath, fragPath);
}

Shader::~Shader()
{
	DEBUG(glDeleteProgram(m_rendererID));
}

void Shader::bind() const
{
	DEBUG(glUseProgram(m_rendererID));
}

void Shader::unbind() const
{
	DEBUG(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, int value)
{
	DEBUG(glUniform1i(uniformLoc(name), value));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	DEBUG(glUniform4f(uniformLoc(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	DEBUG(glUniformMatrix4fv(uniformLoc(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

int Shader::uniformLoc(const std::string& name)
{
	if (m_uniformLocations.find(name) != m_uniformLocations.end())
	{
		return m_uniformLocations[name];
	}

	DEBUG(int location = glGetUniformLocation(m_rendererID, name.c_str()));
	if (location != -1)
	{
		std::cout << "[OPENGL WARN]: uniform '" << name << "' doesn't exist" << std::endl;
	}
	m_uniformLocations[name] = location;
	return location;
}
