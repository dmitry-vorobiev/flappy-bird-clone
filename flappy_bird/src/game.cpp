#include "game.h"
#include "input.h"
#include "utils/system_clock.h"

#include <iostream>
#include <cstdio>

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
	utils::SystemClock time;
	uint64_t lastTime = time.nanosec();
	uint64_t timer = time.millisec();

	double delta = 0.0;
	double ns = 1000000000 / 60.0;
	int updates = 0;
	int frames = 0;

	char title[128];

	while (m_active)
	{
		uint64_t now = time.nanosec();
		delta += (now - lastTime) / ns;
		lastTime = now;

		if (delta >= 1.0)
		{
			update();
			updates++;
			delta--;
		}

		render();
		frames++;

		if (time.millisec() - timer > 1000)
		{
			sprintf_s(title, "Flappy Bird | UPD: %i, FPS: %i", updates, frames);
			glfwSetWindowTitle(m_window, title);

			timer += 1000;
			updates = 0;
			frames = 0;
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
	
	if (input::is_key_pressed(GLFW_KEY_ESCAPE))
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
