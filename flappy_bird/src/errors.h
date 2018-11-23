#pragma once

#define ASSERT(x) if (!(x)) __debugbreak()
#define DEBUG(x) glClearErrors(); x; ASSERT(glLogErrors(#x, __FILE__, __LINE__))

void glClearErrors();
bool glLogErrors(const char* funcName, const char* fileName, int line);

