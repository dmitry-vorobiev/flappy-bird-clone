#include <glm/gtc/type_ptr.hpp>

#include "ext_deps.h"
#include "shader.h"
#include "errors.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


Shader::Shader(
	const std::string& vert_src_path, 
	const std::string& frag_src_path
)
	:m_ID(0), m_vert_path(vert_src_path), m_frag_path(frag_src_path)
{
	m_ID = shader_utils::build(m_vert_path, m_frag_path);
}

Shader::~Shader()
{
	DEBUG(glDeleteProgram(m_ID));
}

void Shader::bind() const
{
	DEBUG(glUseProgram(m_ID));
}

void Shader::unbind() const
{
	DEBUG(glUseProgram(0));
}

void Shader::set_uniform_1i(const std::string& name, int value)
{
	DEBUG(glUniform1i(uniform_loc(name), value));
}

void Shader::set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	DEBUG(glUniform4f(uniform_loc(name), v0, v1, v2, v3));
}

void Shader::set_uniform_mat4f(const std::string& name, const glm::mat4& matrix)
{
	DEBUG(glUniformMatrix4fv(uniform_loc(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

int Shader::uniform_loc(const std::string& name)
{
	if (m_uniform_locations.find(name) != m_uniform_locations.end())
	{
		return m_uniform_locations[name];
	}

	DEBUG(int location = glGetUniformLocation(m_ID, name.c_str()));
	if (location != -1)
	{
		std::cout << "[OPENGL WARN]: uniform '" << name << "' doesn't exist" << std::endl;
	}
	m_uniform_locations[name] = location;
	return location;
}
