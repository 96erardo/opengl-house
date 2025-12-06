#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	glEnable(GL_DEPTH_TEST);

	Shader shader("res/shaders/Basic.shader");

	float data[] = {
		// Walls
		 0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,-0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,-0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f,

		 0.5f, 0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,-0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,-0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,  1.0f, 1.0f, 1.0f,

		// Ceiling
		 0.0f, 1.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, 0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	};

	unsigned int wallIndex[] = {
		0, 1, 2,
		0, 2, 3,

		3, 2, 6,
		3, 6, 7,

		4, 5, 6,
		4, 6, 7,

		0, 1, 5,
		0, 4, 5
	};

	unsigned int ceilIndex[] = {
		8,  9, 10,
		8, 10, 12,
		8, 11, 12,
		8, 12, 11
	};

	VertexBuffer vb(&data, sizeof(float) * 6 * 13);
	IndexBuffer  ceilIb(ceilIndex, 3 * 4);
	IndexBuffer ib(wallIndex, 6 * 4);
	VertexArray va;
	VertexBufferLayout layout;
	Renderer renderer;

	layout.Push<float>(3);
	layout.Push<float>(3);

	va.addLayout(vb, layout);

	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();		

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view  = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.5f));
		view = glm::rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		shader.Bind();
		shader.setUniformM4f("model", model);
		shader.setUniformM4f("view", view);
		shader.setUniformM4f("projection", projection);
		shader.Unbind();

		renderer.draw(va, ib, shader);
		renderer.draw(va, ceilIb, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}