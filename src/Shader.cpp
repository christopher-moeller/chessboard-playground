#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#define LOG_SHADER_INIT false


Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
    
    std::string vertexShaderSource = LoadShaderSource(vertexShaderPath);
    std::string fragmentShaderSource = LoadShaderSource(fragmentShaderPath);
    
    GLuint vertexShader = CompileShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    GLint success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader Program Linking Failed\n" << infoLog << std::endl;
        return;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    this->m_ShaderProgram = shaderProgram;
    
}

Shader::~Shader() {
    glDeleteProgram(this->m_ShaderProgram);
}

std::string Shader::LoadShaderSource(std::string filepath) {
    std::string fullpath = SHADER_PATH_PREFIX + filepath;
    std::ifstream file(fullpath.c_str());
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << fullpath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string shaderContent = buffer.str();
    
    if(LOG_SHADER_INIT) {
        std::cout << "Shader '" << fullpath << "' successfully loaded: " << std::endl;
        std::cout << shaderContent << std::endl;
    }

    
    return shaderContent;
}

GLint Shader::CompileShader(const char *source, GLint shaderType) {
    GLuint glShader = glCreateShader(shaderType);
    glShaderSource(glShader, 1, &source, nullptr);
    glCompileShader(glShader);
    
    // Check for compilation errors
    GLint success;
    char infoLog[512];
    glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(glShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
        return -1;
    }
    
    return glShader;
}

void Shader::Use() {
    glUseProgram(this->m_ShaderProgram);
}

void Shader::SetUniform4Mat(const char *varName, glm::mat4 mat) {
    int varPos = glGetUniformLocation(this->m_ShaderProgram, varName);
    glUniformMatrix4fv(varPos, 1, GL_FALSE, glm::value_ptr(mat));
}
