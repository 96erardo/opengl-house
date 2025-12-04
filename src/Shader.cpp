#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include "Shader.h"

Shader::Shader(const std::string& filepath) {
    ShaderSource source = parseShader(filepath);
    m_id = createShaders(source.VertexSource, source.FragmentSource);

    glUseProgram(m_id);
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}

unsigned int Shader::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(m_id, name.c_str());
}

void Shader::setUniform1i(const std::string& name, int i0) {
    glUniform1i(getUniformLocation(name), i0);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    glUniform4f(getUniformLocation(name), v0, v1, v2, v2);
}

//void Shader::setUniformM4f(const std::string& name, const glm::mat4& m) {
//    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
//}

void Shader::Bind() const {
    glUseProgram(m_id);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

ShaderSource Shader::parseShader(const std::string& filepath) {
    std::ifstream file(filepath);
    std::stringstream ss[2];
    std::string line;

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    while (getline(file, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(GLenum type, const std::string& shader) {
    unsigned int id = glCreateShader(type);
    const char* src = shader.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    return id;
}

unsigned int Shader::createShaders(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}