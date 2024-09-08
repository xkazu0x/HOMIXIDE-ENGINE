#include "grid.h"

Grid::Grid(int width, int height) :
	m_width(width), m_height(height), m_cell_size(0.5f) {
	std::vector<Vertex> vertices = {};
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			vertices.push_back(Vertex(glm::vec3(x - m_cell_size, 0.0f, y - m_cell_size)));
			vertices.push_back(Vertex(glm::vec3(x + m_cell_size, 0.0f, y + m_cell_size)));
			vertices.push_back(Vertex(glm::vec3(x + m_cell_size, 0.0f, y - m_cell_size)));

			vertices.push_back(Vertex(glm::vec3(x - m_cell_size, 0.0f, y - m_cell_size)));
			vertices.push_back(Vertex(glm::vec3(x - m_cell_size, 0.0f, y + m_cell_size)));
			vertices.push_back(Vertex(glm::vec3(x + m_cell_size, 0.0f, y + m_cell_size)));
		}
	}

	m_mesh = new Mesh(vertices);
}

Grid::~Grid() {
	delete m_mesh;
}

void Grid::Draw(Shader* shader) {
	glm::mat4 model(1.0f);
	shader->SetUniformMatrix("model", model);
	m_mesh->Draw(GL_LINE_LOOP);
}
