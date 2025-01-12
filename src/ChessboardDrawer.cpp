#include "ChessboardDrawer.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

ChessboardDrawer::ChessboardDrawer(Chessboard* chessboard)
{
    this->m_Chessboard = chessboard;
}

ChessboardDrawer::~ChessboardDrawer()
{
}

int ChessboardDrawer::Setup() {
    
    int countRows = m_Chessboard->GetY();
    int countColumns = m_Chessboard->GetX();
    
    std::vector<float> verticies;
    std::vector<unsigned int> indices;
    
    int normalizeBy = countRows > countColumns ? countRows : countColumns;
    
    int rectangleCount = 0;
    for (int row=0; row<countRows; row++) {
        
        for (int column=0; column<countColumns; column++) {
            
            float r1 = (static_cast<float>(row) / normalizeBy) - 0.5f;
            float r2 = (static_cast<float>(row + 1) / normalizeBy) - 0.5f;
            
            float c1 = (static_cast<float>(column) / normalizeBy) - 0.5f;
            float c2 = (static_cast<float>(column + 1) / normalizeBy) - 0.5f;
            
            float colorValue = static_cast<float>((row + column) % 2);
            
            float rectangleVertices[] = {
                c1,  r1, 0.0f, colorValue, colorValue, colorValue, // Bottom-left
                c2,  r1, 0.0f, colorValue, colorValue, colorValue, // Bottom-right
                c1,  r2, 0.0f, colorValue, colorValue, colorValue, // Top-left
                c2,  r2, 0.0f, colorValue, colorValue, colorValue, // Top-right
            };
            
            for(size_t i = 0; i < 4 * 6; i++) {
                verticies.push_back(rectangleVertices[i]);
            }
            
            unsigned int startIndex = rectangleCount * 4;
            unsigned int rectangleIndices[] = {
                startIndex, startIndex + 1, startIndex + 2,
                startIndex + 2, startIndex + 1, startIndex + 3,
            };
            
            for(size_t i = 0; i < 2 * 3; i++) {
                indices.push_back(rectangleIndices[i]);
            }
            
            rectangleCount++;
            
        }
        
        
    }
    
    this->m_Shader = new Shader("rectangle-vert.glsl", "rectangle-frag.glsl");
    
    this->m_VertexBuffer.SetVertices(verticies);
    this->m_VertexBuffer.SetIndices(indices);
    
    this->m_VertexBuffer.AddAttributePointers(3, 6);
    this->m_VertexBuffer.AddAttributePointers(3, 6);
    
    this->m_VertexBuffer.Apply();
    
    return 0;
    
}

int ChessboardDrawer::CleanUp() {
    delete this->m_Shader;
}

void ChessboardDrawer::Draw(Camera* camera) {
    this->m_Shader->Use();
    this->m_VertexBuffer.Bind();
    
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();
    this->m_Shader->SetUniform4Mat("view", view);
    this->m_Shader->SetUniform4Mat("projection", projection);
    
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    this->m_Shader->SetUniform4Mat("model", model);
    
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(this->m_VertexBuffer.GetIndicesCount()), GL_UNSIGNED_INT, 0);
}
