#pragma once

#include "../graphics/shader.h"
#include "../graphics/mesh.h"

#include <stdint.h>

class Grid {
public:
	Grid(int width, int height);
	~Grid();

	void Draw(Shader* shader);

private:
	int m_width;
	int m_height;
	float m_cell_size;

	Mesh* m_mesh;
};
