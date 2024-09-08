#version 330

in vec3 a_color;
in vec2 a_uv;

out vec4 f_color;

uniform sampler2D s_texture;

void main() {
	//f_color = vec4(a_color, 1.0);
	vec3 result = a_color * vec3(texture(s_texture, a_uv));
	f_color = vec4(result, 1.0);
}