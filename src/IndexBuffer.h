#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer {
private:
	unsigned int m_id;
	unsigned int m_count;
public:
	IndexBuffer(const unsigned int* indices, unsigned int count);
	~IndexBuffer();

	unsigned int getCount() const;

	void Bind() const;
	void Unbind() const;
};

#endif