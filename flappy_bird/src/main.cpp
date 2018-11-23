#include <iostream>

#include "game.h"


int main() 
{
	if (!glfwInit())
	{
		std::cout << "Unable to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	int width = 1280;
	int height = 720;

	GLFWwindow* window = glfwCreateWindow(width, height, "Flappy bird", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Unable to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(window,
		(vidmode->width - width) / 2,
		(vidmode->height - height) / 2
	);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

	{
		Game game(window, width, height);
		game.start();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}