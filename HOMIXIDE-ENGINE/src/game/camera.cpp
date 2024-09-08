#include "camera.h"
#include "../window/window.h"

#include <glm/ext.hpp>

Camera::Camera(glm::vec3 position, float fov) :
	m_position(position), m_fov(fov), m_rotation(1.0f) {
	UpdateVectors();
}

Camera::~Camera() {
}

void Camera::Rotate(float x, float y, float z) {
	m_rotation = glm::rotate(m_rotation, z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_rotation = glm::rotate(m_rotation, y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_rotation = glm::rotate(m_rotation, x, glm::vec3(1.0f, 0.0f, 0.0f));

	UpdateVectors();
}

glm::mat4 Camera::GetProjection() {
	float aspect = Window::GetWindowAspect();
	return glm::perspective(m_fov, aspect, 0.1f, 100.0f);
}

glm::mat4 Camera::GetView() {
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::UpdateVectors() {
	m_front = glm::vec3(m_rotation * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
	m_up	= glm::vec3(m_rotation * glm::vec4(0.0f, 1.0f,  0.0f, 1.0f));
	m_right = glm::vec3(m_rotation * glm::vec4(1.0f, 0.0f,  0.0f, 1.0f));
}