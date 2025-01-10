# pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

#define SHADER_PATH_PREFIX "../../shaders/"

class Shader
{
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~Shader();
    
    void Use();
    void SetUniform4Mat(const char* varName, glm::mat4 mat);
    
private:
    GLuint m_ShaderProgram;
    std::string LoadShaderSource(std::string filepath);
    GLint CompileShader(const char *source, GLint shaderType);
};
