#include <iostream>
#include <glad/glad.h>
#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture (const std::string& filepath): m_path(filepath) {
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	std::string extension = m_path.substr(m_path.find_last_of(".") + 1);

	unsigned char* data = stbi_load(m_path.c_str(), &m_width, &m_height, &m_nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, extension == "png" ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture..." << std::endl;
	}

	stbi_image_free(data);
}

inline int Texture::getWidth() const { return m_width; }

inline int Texture::getHeight() const { return m_height; }

void Texture::Activate(unsigned int i) const {
	glActiveTexture(i);
	Bind();
}

void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}
