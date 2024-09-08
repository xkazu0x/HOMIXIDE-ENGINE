#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices);
	~Mesh();

	void Draw(unsigned int mode);
	
private:
	unsigned int m_vao;
	unsigned int m_vbo;
	std::vector<Vertex> m_vertices;
};
