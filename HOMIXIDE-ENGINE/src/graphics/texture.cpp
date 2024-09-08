#include "Texture.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"

Texture::Texture(unsigned int id, int width, int height, int channels) :
	m_id(id), m_width(width), m_height(height), m_channels(channels) {
}

Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, m_id);
}

unsigned int LoadImage(const char* path, int* width, int* height, int* channels, bool flip) {
	unsigned int texture;

	stbi_set_flip_vertically_on_load(flip);
	unsigned char* data = stbi_load(path, width, height, channels, 0);
	if (data) {
		GLenum format = GL_NONE;
		if (*channels == 1) format = GL_RED;
		else if (*channels == 3) format = GL_RGB;
		else if (*channels == 4) format = GL_RGBA;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, format, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		return 0;
	}
	stbi_image_free(data);

	return texture;
}

Texture* LoadTexture(std::string filename) {
	int width, height, channels;
	unsigned int id = LoadImage(filename.c_str(), &width, &height, &channels, true);
	if (!id) {
		std::cerr << "Could not load image " << filename << "\n";
	}

	return new Texture(id, width, height, channels);
}