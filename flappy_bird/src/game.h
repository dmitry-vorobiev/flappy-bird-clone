#pragma once

#include "ext_deps.h"

class Game
{
private:
	int m_width, m_height;
	bool m_active;
	GLFWwindow* m_window;

public:
	Game(int width, int height);
	~Game();

	void run();

private:
	void init();
	void update();
	void render();
};
