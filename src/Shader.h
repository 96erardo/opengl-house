#pragma once
#include <string>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

struct ShaderSource { std::string VertexSource, FragmentSource; };

class Shader {
private:
	unsigned int m_id;

	ShaderSource parseShader(const std::string& filepath);
	unsigned int compileShader(GLenum type, const std::string& shader);
	unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int getUniformLocation(const std::string& name);

public:
	Shader(const std::string& filepath);
	~Shader();

	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string& name, int i1);
	// void setUniformM4f(const std::string& name, const glm::mat4& m);

	void Bind() const;
	void Unbind() const;
};