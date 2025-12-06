 #include "glad/glad.h"
#include "Renderer.h"

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(const VertexArray& va, const Shader& shader, unsigned int count) const {
    shader.Bind();
    va.Bind();

    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::clear() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}