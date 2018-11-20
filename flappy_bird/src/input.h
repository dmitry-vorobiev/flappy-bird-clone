#pragma once

#include <GLFW/glfw3.h>

namespace input
{
	bool keys[512]{false};

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		keys[key] = action != GLFW_RELEASE;
	}

	inline bool is_key_pressed(int key) { return keys[key]; }
};