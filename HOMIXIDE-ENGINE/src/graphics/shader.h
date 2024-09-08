#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
	Shader(unsigned int id);
	~Shader();

	void Use();
	void SetUniformMatrix(std::string name, glm::mat4 matrix);

private:
	unsigned int m_id;
};

extern Shader* CreateShaderProgram(std::string vertex_filepath, std::string fragment_filepath);
