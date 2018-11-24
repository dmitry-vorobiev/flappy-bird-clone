#pragma once

#include <string>

namespace utils 
{
	namespace files 
	{
		bool loadToString(const std::string& path, std::string& out);
	}
}