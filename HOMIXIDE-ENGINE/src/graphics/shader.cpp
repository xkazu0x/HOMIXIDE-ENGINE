#include "shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(unsigned int id) :
	m_id(id) {
}

Shader::~Shader() {
	glDeleteProgram(m_id);
}

void Shader::Use() {
	glUseProgram(m_id);
}

void Shader::SetUniformMatrix(std::string name, glm::mat4 matrix) {
	unsigned int uniform_location = glGetUniformLocation(m_id, name.c_str());
	glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader* CreateShaderProgram(std::string vertex_filepath, std::string fragment_filepath) {
	// Read Files
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vert_shader_file;
	std::ifstream frag_shader_file;

	vert_shader_file.exceptions(std::ifstream::badbit);
	frag_shader_file.exceptions(std::ifstream::badbit);
	try {
		vert_shader_file.open(vertex_filepath);
		frag_shader_file.open(fragment_filepath);

		std::stringstream vert_shader_stream, frag_shader_stream;
		vert_shader_stream << vert_shader_file.rdbuf();
		frag_shader_stream << frag_shader_file.rdbuf();

		vert_shader_file.close();
		frag_shader_file.close();

		vertex_code = vert_shader_stream.str();
		fragment_code = frag_shader_stream.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
		return nullptr;
	}

	const char* vertex_shader_code = vertex_code.c_str();
	const char* fragment_shader_code = fragment_code.c_str();

	unsigned int vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_shader_code, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cerr << "SHADER::VERTEX::COMPILATION_FAILED\n";
		std::cerr << infoLog << "\n";
		return nullptr;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_shader_code, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cerr << "SHADER::FRAGMENT::COMPILATION_FAILED\n";
		std::cerr << infoLog << "\n";
		return nullptr;
	}

	// Shader Program
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "SHADER::PROGRAM::LINKING_FAILED\n";
		std::cerr << infoLog << "\n";
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return nullptr;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return new Shader(program);
}
