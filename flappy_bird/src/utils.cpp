#include "ext_deps.h"
#include "utils.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

bool files::loadToString(const std::string& path, std::string& out)
{
	std::ifstream stream(path);

	if (!stream.is_open())
	{
		std::cout << "[I/O ERROR] Unable to read from " << path << std::endl;
		return false;
	}

	std::stringstream ss;
	ss << stream.rdbuf();
	stream.close();
	out = ss.str();

	return true;
}

unsigned int shader::build(
	const std::string& vert_src_path,
	const std::string& frag_src_path)
{
	std::string vert_src;
	std::string frag_src;

	bool vert_src_ok = files::loadToString(vert_src_path, vert_src);
	bool frag_src_ok = files::loadToString(frag_src_path, frag_src);

	if (vert_src_ok && frag_src_ok)
	{
		unsigned int vs = compile(GL_VERTEX_SHADER, vert_src);
		unsigned int fs = compile(GL_FRAGMENT_SHADER, frag_src);
		return link(vs, fs);
	}

	return 0;
}


unsigned int shader::compile(unsigned int type, const std::string& source)
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

unsigned int shader::link(unsigned int vert_s, unsigned int frag_s)
{
	unsigned int prog = glCreateProgram();

	glAttachShader(prog, vert_s);
	glAttachShader(prog, frag_s);

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

		glDetachShader(prog, vert_s);
		glDetachShader(prog, frag_s);
		glDeleteProgram(prog);
		prog = 0;
	}

	glDeleteShader(vert_s);
	glDeleteShader(frag_s);

	return prog;

}

uint64_t CurrentTime::millisec()
{
	using namespace std::chrono;

	return duration_cast<milliseconds>(time()).count();
}

uint64_t CurrentTime::nanosec()
{
	using namespace std::chrono;

	return duration_cast<nanoseconds>(time()).count();
}

Duration CurrentTime::time()
{
	return m_clock.now().time_since_epoch();
}
