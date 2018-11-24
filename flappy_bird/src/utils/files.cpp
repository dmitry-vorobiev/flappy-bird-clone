#include "files.h"

#include <iostream>
#include <fstream>
#include <sstream>

bool utils::files::loadToString(const std::string& path, std::string& out)
{
	std::ifstream file(path, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "[I/O ERROR] Unable to read from " << path << std::endl;
		return false;
	}

	std::string line;

	while (!file.eof())
	{
		getline(file, line);
		out.append(line + "\n");
	}

	file.close();
	return true;
}