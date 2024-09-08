#version 330

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec2 v_uv;

out vec3 a_color;
out vec2 a_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	a_color = v_color;
	a_uv = v_uv;
	gl_Position = projection * view * model * vec4(v_position, 1.0);
}