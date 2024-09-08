#include "maze.h"

#include <random>
#include <glm/ext.hpp>

Maze::Maze(int width, int height) :
	m_width(width), m_height(height), m_floor_size(0.5f), m_wall_size(2.0f), m_grid(), m_meshes() {
	m_grid.resize(width * height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			m_grid[x + y * width].x = x;
			m_grid[x + y * width].y = y;
		}
	}

	// Generate Maze
	std::vector<Cell*> stack = {};

	Cell* current = &m_grid[0];
	current->visited = true;
	for (int g = 0; g < m_grid.size() + stack.size() * stack.size(); g++) {
		Cell* next = CheckNeighbors(current);
		if (next->isNeighbor) {
			next->visited = true;
			// PUSH TO STACK
			stack.push_back(current);
			// REMOVE WALLS
			int x = next->x - current->x;
			if (x == 1) {
				current->walls[3] = false;
				next->walls[1] = false;
			}
			else if (x == -1) {
				current->walls[1] = false;
				next->walls[3] = false;
			}

			int y = next->y - current->y;
			if (y == 1) {
				current->walls[0] = false;
				next->walls[2] = false;
			}
			else if (y == -1) {
				current->walls[2] = false;
				next->walls[0] = false;
			}
			current = next;
		}
		else if (stack.size() > 0) {
			stack.pop_back();
			current = stack[stack.size() - 1];
		}
	}

	// Draw Maze
	glm::vec3 floor_color(1.0f);
	glm::vec3 wall_color(0.8f);

	for (Cell cell : m_grid) {
		// floor
		m_floor.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y - m_floor_size), floor_color, glm::vec2(0, 0)));
		m_floor.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y + m_floor_size), floor_color, glm::vec2(1, 1)));
		m_floor.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y - m_floor_size), floor_color, glm::vec2(1, 0)));

		m_floor.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y - m_floor_size), floor_color, glm::vec2(0, 0)));
		m_floor.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y + m_floor_size), floor_color, glm::vec2(0, 1)));
		m_floor.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y + m_floor_size), floor_color, glm::vec2(1, 1)));

		// walls
		// front
		if (cell.walls[0]) {
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y + m_floor_size), wall_color, glm::vec2(0, 0)));
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, m_wall_size, cell.y + m_floor_size), wall_color, glm::vec2(1, 1)));
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y + m_floor_size), wall_color, glm::vec2(1, 0)));

			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y + m_floor_size), wall_color, glm::vec2(0, 0)));
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, m_wall_size, cell.y + m_floor_size), wall_color, glm::vec2(0, 1)));
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, m_wall_size, cell.y + m_floor_size), wall_color, glm::vec2(1, 1)));
		}

		// left
		if (cell.walls[1]) {
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y - m_floor_size), wall_color, glm::vec2(0, 0)));
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, m_wall_size, cell.y + m_floor_size), wall_color, glm::vec2(1, 1)));
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y + m_floor_size), wall_color, glm::vec2(1, 0)));

			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y - m_floor_size), wall_color, glm::vec2(0, 0)));
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, m_wall_size, cell.y - m_floor_size), wall_color, glm::vec2(0, 1)));
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, m_wall_size, cell.y + m_floor_size), wall_color, glm::vec2(1, 1)));
		}

		// back
		if (cell.walls[2]) {
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y - m_floor_size), wall_color, glm::vec2(0, 0)));
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, m_wall_size, cell.y - m_floor_size), wall_color, glm::vec2(1, 1)));
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, 0.0f, cell.y - m_floor_size), wall_color, glm::vec2(1, 0)));

			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y - m_floor_size), wall_color, glm::vec2(0, 0)));
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, m_wall_size, cell.y - m_floor_size), wall_color, glm::vec2(0, 1)));
			m_walls.push_back(Vertex(glm::vec3(cell.x - m_floor_size, m_wall_size, cell.y - m_floor_size), wall_color, glm::vec2(1, 1)));
		}

		// right
		if (cell.walls[3]) {
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y + m_floor_size), wall_color, glm::vec2(0, 0)));
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, m_wall_size, cell.y - m_floor_size), wall_color, glm::vec2(1, 1)));
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y - m_floor_size), wall_color, glm::vec2(1, 0)));

			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, 0.0f, cell.y + m_floor_size), wall_color, glm::vec2(0, 0)));
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, m_wall_size, cell.y + m_floor_size), wall_color, glm::vec2(0, 1)));
			m_walls.push_back(Vertex(glm::vec3(cell.x + m_floor_size, m_wall_size, cell.y - m_floor_size), wall_color, glm::vec2(1, 1)));
		}
	}

	m_meshes.push_back(new Mesh(m_floor, "res/textures/concrete-floor.png"));
	m_meshes.push_back(new Mesh(m_walls, "res/textures/concrete-wall.png"));
}

Maze::~Maze() {
	for (Mesh* mesh : m_meshes) {
		delete mesh;
	}
}

void Maze::Draw(Shader* shader) {
	for (Mesh* mesh : m_meshes) {
		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(2.0f));

		shader->Use();
		shader->SetUniformMatrix("model", model);

		//mesh->Draw(GL_LINE_LOOP);
		mesh->Draw(GL_TRIANGLES);
	}
}

Cell* Maze::CheckNeighbors(const Cell* cell) {
	Cell* top = &m_grid[GetIndex(cell->x, cell->y - 1)];
	Cell* right = &m_grid[GetIndex(cell->x + 1, cell->y)];
	Cell* bottom = &m_grid[GetIndex(cell->x, cell->y + 1)];
	Cell* left = &m_grid[GetIndex(cell->x - 1, cell->y)];

	std::vector<Cell*> neighbors = {};
	if (!top->visited)		neighbors.push_back(top);
	if (!right->visited)	neighbors.push_back(right);
	if (!bottom->visited)	neighbors.push_back(bottom);
	if (!left->visited)		neighbors.push_back(left);

	if (neighbors.size() > 0) {
		std::random_device dev;
		std::mt19937 random(dev());
		std::uniform_int_distribution<uint32_t> dist(0, (neighbors.size() - 1));
		int r = dist(random);
		neighbors[r]->isNeighbor = true;
		return neighbors[r];
	}
	else {
		return new Cell();
	}
}

int Maze::GetIndex(int x, int y) {
	if (x < 0 || y < 0 || x > m_width - 1 || y > m_height - 1)
		return 0;

	return x + y * m_width;
}
