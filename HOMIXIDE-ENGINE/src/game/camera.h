#pragma once

#include <glm/glm.hpp>

class Camera {
public:
	Camera(glm::vec3 position, float fov);
	~Camera();

	void Rotate(float x, float y, float z);

	glm::mat4 GetProjection();
	glm::mat4 GetView();

private:
	void UpdateVectors();

public:
	float m_fov;
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::mat4 m_rotation;
};
