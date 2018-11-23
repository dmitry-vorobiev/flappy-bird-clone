#include "game.h"
#include "input.h"

#include <iostream>

Game::Game(GLFWwindow* window, int width, int height)
	:m_width(width), m_height(height), m_active(false), m_window(window)
{}

Game::~Game() 
{
}

void Game::start()
{
	m_active = true;
	init();
	run();
}

void Game::run()
{
	while (m_active)
	{
		update();
		render();
	}
}

void Game::init()
{
	glfwSetKeyCallback(m_window, input::key_callback);
}

void Game::update()
{
	glfwPollEvents();
	
	if (input::is_key_pressed(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(m_window, GL_TRUE);
		m_active = false;
	}
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_level.render();
	glfwSwapBuffers(m_window);
}
