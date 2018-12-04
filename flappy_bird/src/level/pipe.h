#pragma once

#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/vertex_array.h"

#include "glm/glm.hpp"

struct PipeAssets
{
	VertexArray mesh;
	Texture texture;
	Shader shader;
};

class Pipe
{
public:
	static constexpr float WIDTH = 2.0f;
	static constexpr float HEIGHT = 8.0f;

private:
	static PipeAssets* s_assets;
	glm::vec3 m_position;
	glm::mat4 m_modelMatrix;

public:
	Pipe(float x, float y);

	inline float x() { return m_position.x;  }
	inline float y() { return m_position.y;  }
	inline glm::mat4& modelMatrix() { return m_modelMatrix; }

	inline static VertexArray& mesh() { return s_assets->mesh; }
	inline static Texture& texture() { return s_assets->texture; }
	inline static Shader& shader() { return s_assets->shader; }

	static void init();
	static void destroy();
};