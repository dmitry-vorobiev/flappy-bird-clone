#include "game.h"
#include "input.h"

#include <iostream>

Game::Game(GLFWwindow* window, int width, int height)
	:m_width(width), m_height(height), m_active(false), 
	m_window(window)
{}

Game::~Game() 
{
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
	glfwSetKeyCallback(m_window, input::key_callback);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_level.render();
	glfwSwapBuffers(m_window);
}
