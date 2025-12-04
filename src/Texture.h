#pragma once
#include<string>

class Texture {
private:
	unsigned int m_id = 0;
	int m_width       = 0;
	int m_height      = 0; 
	int m_nrChannels  = 0;
	std::string m_path;

public:
	Texture(const std::string& filepath);

	inline int getWidth() const;
	inline int getHeight() const;

	void Activate(unsigned int i) const;

	void Bind() const;
	void Unbind() const;
};