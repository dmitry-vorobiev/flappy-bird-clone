#include "files.h"

#include <iostream>
#include <fstream>
#include <sstream>

bool utils::files::loadToString(const std::string& path, std::string& out)
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