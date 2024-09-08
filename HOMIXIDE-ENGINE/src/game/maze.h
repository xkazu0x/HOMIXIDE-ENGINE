#pragma once

#include "../graphics/shader.h"
#include "../graphics/mesh.h"

#include <stdint.h>
#include <stack>

struct Cell {
	Cell() :
		x(), y(), visited(false), walls() {
		walls = { true, true, true, true};
	}

	int x;
	int y;
	bool visited;
	std::vector<bool> walls;
	bool isNeighbor = false;
};

class Maze {
public:
	Maze(int width, int height);
	~Maze();

	void Draw(Shader* shader);

private:
	Cell* CheckNeighbors(const Cell* cell);
	int GetIndex(int x, int y);

private:
	int m_width;
	int m_height;

	float m_floor_size;
	float m_wall_size;

	std::vector<Cell> m_grid;
	std::vector<Mesh*> m_meshes;
	std::vector<Vertex> m_floor = {};
	std::vector<Vertex> m_walls = {};
};
