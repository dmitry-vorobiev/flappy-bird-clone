#pragma once

#include "ext_deps.h"

namespace input
{
	static bool keys[512];

	inline void callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		keys[key + 1] = action != GLFW_RELEASE;
	}

	inline bool isKeyDown(int key) { return keys[key + 1]; }
};