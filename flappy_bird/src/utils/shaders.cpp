#include "shaders.h"
#include "files.h"
#include "../ext_deps.h"

#include <iostream>

unsigned int utils::shaders::build(
	const std::string& vertSrcPath,
	const std::string& fragSrcPath)
{
	std::string vertSrc;
	std::string fragSrc;

	bool vertSrcLoaded = files::loadToString(vertSrcPath, vertSrc);
	bool fragSrcLoaded = files::loadToString(fragSrcPath, fragSrc);

	if (vertSrcLoaded && fragSrcLoaded)
	{
		unsigned int vs = compile(GL_VERTEX_SHADER, vertSrc);
		unsigned int fs = compile(GL_FRAGMENT_SHADER, fragSrc);
		return link(vs, fs);
	}

	return 0;
}


unsigned int utils::shaders::compile(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, log);

		std::cout
			<< "[OPENGL ERROR]: Unable to compile "
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader. Sorry, master...\n"
			<< log << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int utils::shaders::link(unsigned int vertShaderID, unsigned int fragShaderID)
{
	unsigned int prog = glCreateProgram();

	glAttachShader(prog, vertShaderID);
	glAttachShader(prog, fragShaderID);

	glLinkProgram(prog);

	int linked;
	glGetProgramiv(prog, GL_LINK_STATUS, &linked);

	if (linked == GL_FALSE)
	{
		int length;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(prog, length, &length, log);

		std::cout
			<< "[OPENGL ERROR]: Unable to link shaders into program.\n"
			<< log << std::endl;

		glDetachShader(prog, vertShaderID);
		glDetachShader(prog, fragShaderID);
		glDeleteProgram(prog);
		prog = 0;
	}

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

	return prog;

}