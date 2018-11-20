#pragma once

#define ASSERT(x) if (!(x)) __debugbreak()
#define DEBUG(x) gl_clear_errors(); x; ASSERT(gl_log_errors(#x, __FILE__, __LINE__))

void gl_clear_errors();
bool gl_log_errors(const char* funcName, const char* fileName, int line);

