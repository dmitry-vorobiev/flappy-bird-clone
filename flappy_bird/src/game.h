#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
