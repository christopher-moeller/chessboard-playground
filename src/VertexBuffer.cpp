#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::SetVertices(std::vector<float> vertices) {
    this->m_Vertices = vertices;
}

void VertexBuffer::SetIndices(std::vector<unsigned int> indices) {
    this->m_Indices = indices;
}

void VertexBuffer::AddAttributePointers(GLuint attributeSizePerVertex, GLuint vertextSize) {
    VertexAttributePointer attributePointer(attributeSizePerVertex, vertextSize);
    this->m_AttributePointers.push_back(attributePointer);
}

void VertexBuffer::Apply() {
    
    float* verticesArray = new float[m_Vertices.size()];
    for (size_t i = 0; i < m_Vertices.size(); ++i) {
        verticesArray[i] = m_Vertices[i];
    }
    
    unsigned int* indicesArray = new unsigned int[m_Indices.size()];
    for(size_t i = 0; i < m_Indices.size(); i++) {
        indicesArray[i] = m_Indices[i];
    }
        
    // Generate and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &(this->m_VAO));
    glBindVertexArray(this->m_VAO);

    // Generate and bind a Vertex Buffer Object (VBO)
    glGenBuffers(1, &(this->m_VBO));
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), verticesArray, GL_STATIC_DRAW);

    // Generate and bind an Element Buffer Object (EBO)
    glGenBuffers(1, &(this->m_EBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Indices.size(), indicesArray, GL_STATIC_DRAW);

    for(size_t i = 0; i<this->m_AttributePointers.size(); i++) {
        
        VertexAttributePointer attributerPointer =  this->m_AttributePointers[i];
        
        glVertexAttribPointer(i, attributerPointer.getAttributeSizePerVertex(), GL_FLOAT, GL_FALSE, attributerPointer.getVertexSize() * sizeof(float), (void*) (i * 3 * sizeof(float)));
        glEnableVertexAttribArray(i);
        
    }

    // Unbind the VBO (the VAO and EBO should remain bound)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    delete[] indicesArray;
    delete[] verticesArray;
}

void VertexBuffer::Bind() {
    glBindVertexArray(this->m_VAO);
}

size_t VertexBuffer::GetIndicesCount() const {
    return this->m_Indices.size();
};
