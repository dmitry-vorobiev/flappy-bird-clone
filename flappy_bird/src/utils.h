#pragma once

#include <string>

namespace files {
	bool loadToString(const std::string& path, std::string& out);
}

namespace shader
{
	unsigned int compile(unsigned int type, const std::string& src);
	unsigned int link(unsigned int vert_ID, unsigned int frag_ID);
	unsigned int build(const std::string& vert_src_path, const std::string& frag_src_path);
}