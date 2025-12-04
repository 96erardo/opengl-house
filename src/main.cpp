#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

int main() {

	if (!glfwInit())
	{
		std::cout << "Something failed while initializing" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "House", NULL, NULL);

	if (!window)
	{
		std::cout << "Something failed while creating the window and its context" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	Shader shader("res/shaders/Basic.shader");

	float data[] = {
		 0.5f, 0.5f, 0.0f,
		 0.5f,-0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};

	unsigned int index[] = {
		0, 1, 2,
		0, 2, 3
	};

	VertexBuffer vb(&data, sizeof(float) * 3 * 4);
	IndexBuffer ib(index, 6);
	VertexArray va;
	VertexBufferLayout layout;
	Renderer renderer;

	layout.Push<float>(3);

	va.addLayout(vb, layout);

	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		renderer.draw(va, ib, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}