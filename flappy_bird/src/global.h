#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


constexpr float HALF_SCREEN_SIZE_X = 10.0f;
constexpr float HALF_SCREEN_SIZE_Y = HALF_SCREEN_SIZE_X * 9.0f / 16.0f;

const glm::mat4 PROJECTION_MATRIX = glm::ortho(
	-HALF_SCREEN_SIZE_X, HALF_SCREEN_SIZE_X, 
	-HALF_SCREEN_SIZE_Y, HALF_SCREEN_SIZE_Y, 
	-1.0f, 1.0f);
