#include <iostream>
#include <glad/glad.h>
#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_id);
	glBindVertexArray(m_id);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::Bind() const {
	glBindVertexArray(m_id);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::addLayout(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();

	const auto& elements = layout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i, 
			element.count, 
			element.type, 
			element.normalized, 
			layout.getStride(),
			(void*)offset
		);

		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}