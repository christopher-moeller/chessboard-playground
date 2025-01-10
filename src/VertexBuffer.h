# pragma once

#include <vector>
#include <GL/glew.h>

class VertexAttributePointer
{
public:
    VertexAttributePointer(GLuint attributeSizePerVertex, GLuint vertextSize) {
        this->m_AttributeSizePerVertex = attributeSizePerVertex;
        this->m_VertexSize = vertextSize;
    }
    ~VertexAttributePointer() {};
    
    inline GLuint getAttributeSizePerVertex() { return this->m_AttributeSizePerVertex; };
    inline GLuint getVertexSize() { return this->m_VertexSize; };
    
private:
    GLuint m_AttributeSizePerVertex;
    GLuint m_VertexSize;
};

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();
    
    void SetVertices(std::vector<float> vertices);
    void SetIndices(std::vector<unsigned int> indices);
    void AddAttributePointers(GLuint attributeSizePerVertex, GLuint vertextSize);
    void Apply();

private:
    std::vector<float> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<VertexAttributePointer> m_AttributePointers;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};
