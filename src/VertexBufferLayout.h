#pragma once
#include <vector>
#include <glad/glad.h>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return 4;
		}

		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;

public:
	VertexBufferLayout() : m_stride(0) {};
	
	template<typename T>
	void Push (unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_elements.push_back({
			GL_FLOAT,
			count,
			false
		});

		m_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }
	inline const unsigned int getStride() const { return m_stride; }
};