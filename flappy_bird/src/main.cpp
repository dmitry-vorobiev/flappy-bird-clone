#define GLEW_STATIC

#include <iostream>

#include "game.h"


int main() 
{
	Game game(1280, 720);
	game.run();

	return 0;
}