#include "homixide_engine.h"
#include "window/window.h"
#include "window/events.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "game/camera.h"
#include "game/grid.h"

#include <glad/glad.h>
#include <glm/ext.hpp>

namespace Homixide {
	Shader* m_shader = nullptr;
	Camera* m_camera = nullptr;
	float m_speed = 2.5f;
	float m_sens = 0.4f;
	float m_camx = 0.0f;
	float m_camy = 0.0f;

	Grid* m_grid = nullptr;

	void Run() {
		Window::Initialize(1920 / 2, 1080 / 2, "HOMIXIDE ENGINE", false, false);
		Events::Initialize();

		m_shader = CreateShaderProgram("res/shaders/shader.vert", "res/shaders/shader.frag");

		m_camera = new Camera(glm::vec3(0.0f, 1.0f, 2.0f), glm::radians(45.0f));
		m_grid = new Grid(8, 8);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		float last_time = glfwGetTime();
		float delta = 0.0f;
		float now = 0.0f;
		while (Window::WindowIsOpen()) {
			now = glfwGetTime();
			delta = last_time - now;
			last_time = now;

			Events::PollEvents();

			// Update
			if (Events::KeyPressed(GLFW_KEY_ESCAPE)) {
				Window::SetWindowShouldClose(true);
			}
			if (Events::KeyPressed(GLFW_KEY_P)) {
				Window::ToggleFullscreen();
			}
			if (Events::KeyPressed(GLFW_KEY_TAB)) {
				Events::ToggleCursor();
			}

			if (Events::KeyDown(GLFW_KEY_W)) {
				m_camera->m_position -= m_camera->m_front * delta * m_speed;
			}
			if (Events::KeyDown(GLFW_KEY_S)) {
				m_camera->m_position += m_camera->m_front * delta * m_speed;
			}
			if (Events::KeyDown(GLFW_KEY_A)) {
				m_camera->m_position += m_camera->m_right * delta * m_speed;
			}
			if (Events::KeyDown(GLFW_KEY_D)) {
				m_camera->m_position -= m_camera->m_right * delta * m_speed;
			}

			if (Events::KeyDown(GLFW_KEY_SPACE)) {
				m_camera->m_position -= m_camera->m_up * delta * m_speed;
			}
			if (Events::KeyDown(GLFW_KEY_LEFT_SHIFT)) {
				m_camera->m_position += m_camera->m_up * delta * m_speed;
			}

			if (Events::GetCursorLocked()) {
				m_camx += -Events::GetDeltaX() / Window::GetWindowHeight() * m_sens;
				m_camy += -Events::GetDeltaY() / Window::GetWindowHeight() * m_sens;

				if (m_camy < -glm::radians(89.0f)) m_camy = -glm::radians(89.0f);
				if (m_camy > glm::radians(89.0f)) m_camy = glm::radians(89.0f);

				m_camera->m_rotation = glm::mat4(1.0f);
				m_camera->Rotate(m_camy, m_camx, 0.0f);
			}
			
			// Render
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->Use();
			m_shader->SetUniformMatrix("view", m_camera->GetView());
			m_shader->SetUniformMatrix("projection", m_camera->GetProjection());

			m_grid->Draw(m_shader);

			Window::SwapBuffers();
		}
		
		delete m_grid;
		delete m_camera;
		delete m_shader;

		Window::Shutdown();
	}
}