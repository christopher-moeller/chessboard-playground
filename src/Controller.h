#pragma once

#include "Camera.h"
#include "Chessboard.h"
#include "ChessboardDrawer.h"

enum PressedKeys {
    PRESSED_UP,
    PRESSED_DOWN,
    PRESSED_LEFT,
    PRESSED_RIGHT
};

class Controller
{
public:
    Controller();
    ~Controller();
    
    void SetupChessboard();
    void UpdateChessboardDimensions(unsigned int x, unsigned int y);
    inline Chessboard* GetChessboard() { return this->m_Chessboard; };
    void DrawElements();
    void UpdateWindowSize(unsigned int width, unsigned int height);
    void ProcessInput(PressedKeys key, float deltaTime);

private:
    Camera* m_Camera;
    Chessboard* m_Chessboard;
    ChessboardDrawer* m_ChessboardDrawer;
};
