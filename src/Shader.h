# pragma once

#include <string>
#include <GL/glew.h>

#define SHADER_PATH_PREFIX "../../shaders/"

class Shader
{
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~Shader();
    
private:
    GLuint m_ShaderProgram;
    std::string LoadShaderSource(std::string filepath);
    GLint CompileShader(const char *source, GLint shaderType);
    void Use();
};
