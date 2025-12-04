#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray {
private:
	unsigned int m_id;
public:
	VertexArray();
	~VertexArray();
	
	void Bind() const;
	void Unbind() const;

	void addLayout(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

#endif