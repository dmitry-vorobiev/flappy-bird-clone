#include "errors.h"

#include <GL/glew.h>
#include <iostream>

void gl_clear_errors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool gl_log_errors(const char* funcName, const char* fileName, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout
			<< "[OPENGL ERROR]: (" << error << "): "
			<< funcName << " " << fileName << ":" << line
			<< std::endl;
		return false;
	}
	return true;
}