#pragma once

#include "Chessboard.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Camera.h"
#include <GL/glew.h>

class ChessboardDrawer
{
public:
    ChessboardDrawer(Chessboard* chessboard);
    ~ChessboardDrawer();
    
    int Setup();
    int CleanUp();
    void Draw(Camera* camera);
    
private:
    Chessboard* m_Chessboard;
    
    Shader* m_Shader;
    VertexBuffer m_VertexBuffer;
};
