#include "game.h"
#include "input.h"
#include "utils/system_clock.h"

#include <iostream>

Game::Game(GLFWwindow* window, int width, int height) :
	m_width(width), 
	m_height(height), 
	m_active(false), 
	m_window(window),
	m_level()
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
	utils::SystemClock time;
	uint64_t lastTime = time.nanosec();

	double delta = 0.0;
	double ns = 1000000000 / 60.0;

	while (m_active)
	{
		uint64_t now = time.nanosec();
		delta += now - lastTime;
		lastTime = now;

		if (delta > ns)
		{
			delta -= ns;
			update();
		}
		render();
	}
}

void Game::init()
{
	glfwSetKeyCallback(m_window, input::callback);
}

void Game::update()
{
	glfwPollEvents();
	
	if (input::isKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(m_window, GL_TRUE);
		m_active = false;
	}
	m_level.update();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_level.render();
	glfwSwapBuffers(m_window);
}
