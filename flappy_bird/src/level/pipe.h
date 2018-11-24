#pragma once

#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/vertex_array.h"

#include "glm/glm.hpp"

class Pipe
{
private:
	static float s_width, s_height;
	static VertexArray* s_mesh;
	static Texture* s_texture;
	static Shader* s_shader;

	glm::vec3 m_position;
	glm::mat4 m_modelMatrix;

public:
	Pipe(float x, float y);

	inline float x() { return m_position.x;  }
	inline float y() { return m_position.y;  }
	inline glm::mat4& modelMatrix() { return m_modelMatrix; }

	inline static float width() { return s_width; }
	inline static float height() { return s_height; }

	static VertexArray& mesh();
	static Texture& texture();
	static Shader& shader();

	static void init();
	static void destroy();
};