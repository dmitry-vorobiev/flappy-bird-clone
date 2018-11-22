#pragma once

#include "ext_deps.h"
#include "level/level.h"

class Game
{
private:
	int m_width, m_height;
	bool m_active;
	GLFWwindow* m_window;
	Level m_level;

public:
	Game(GLFWwindow* window, int width, int height);
	~Game();

	void run();

private:
	void init();
	void update();
	void render();
};
