#pragma once

#include <string>

class Texture {
public:
	Texture(unsigned int id, int width, int height, int channels);
	~Texture();

	void Bind();

private:
	unsigned int m_id;
	int m_width;
	int m_height;
	int m_channels;
};

extern Texture* LoadTexture(std::string filename);
