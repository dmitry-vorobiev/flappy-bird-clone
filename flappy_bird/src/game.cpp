#include "game.h"
#include "input.h"

#include <iostream>

Game::Game(int width, int height)
	:m_width(width), m_height(height), m_active(false) {}

Game::~Game() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Game::run()
{
	m_active = true;
	init();

	while (m_active)
	{
		update();
		render();

		if (glfwWindowShouldClose(m_window))
		{
			m_active = false;
		}
	}
}

void Game::init()
{
	if (!glfwInit())
	{
		std::cout << "Unable to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(m_width, m_height, "Flappy bird", nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cout << "Unable to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(m_window, 
		(vidmode->width - m_width) / 2, 
		(vidmode->height - m_height) / 2
	);

	glfwSetKeyCallback(m_window, input::key_callback);

	glfwMakeContextCurrent(m_window);
	glfwShowWindow(m_window);
	glfwSwapInterval(1);
}

void Game::update()
{
	glfwPollEvents();
	
	if (input::is_key_pressed(GLFW_KEY_SPACE))
	{
		std::cout << "Test" << std::endl;
	}
	else if (input::is_key_pressed(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(m_window, GL_TRUE);
	}
}

void Game::render()
{
	glfwSwapBuffers(m_window);
}
