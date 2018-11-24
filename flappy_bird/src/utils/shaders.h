#pragma once

#include <string>

namespace utils
{
	namespace shaders
	{
		unsigned int compile(unsigned int shaderType, const std::string& source);
		unsigned int link(unsigned int vertShaderID, unsigned int fragShaderID);
		unsigned int build(const std::string& vertSrcPath, const std::string& fragSrcPath);
	}
}