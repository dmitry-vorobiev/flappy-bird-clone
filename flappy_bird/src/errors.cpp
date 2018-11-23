#include "errors.h"

#include <GL/glew.h>
#include <iostream>

void glClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glLogErrors(const char* funcName, const char* fileName, int line)
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