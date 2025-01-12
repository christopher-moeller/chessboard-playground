#include "Controller.h"
#include <iostream>

Controller::Controller()
{
    this->m_Camera = new Camera(800, 600);
    this->m_Chessboard = new Chessboard();
    this->m_ChessboardDrawer = new ChessboardDrawer(this->m_Chessboard);
}

Controller::~Controller()
{
    delete m_Camera;
    delete m_Chessboard;
    delete m_ChessboardDrawer;
}

void Controller::SetupChessboard() {
    this->m_ChessboardDrawer->Setup();
}

void Controller::UpdateChessboardDimensions(unsigned int x, unsigned int y) {
    this->m_Chessboard->UpdateDimensions(x, y);
}

void Controller::DrawElements() {
    m_ChessboardDrawer->Draw(this->m_Camera);
}

void Controller::UpdateWindowSize(unsigned int width, unsigned int height) {
    this->m_Camera->UpdateWindowSize(width, height);
}

void Controller::ProcessInput(PressedKeys key, float deltaTime) {
    
    if(key == PRESSED_UP) {
        m_Camera->ProcessKeyboard(FORWARD, deltaTime);
    }
    if(key == PRESSED_DOWN) {
        m_Camera->ProcessKeyboard(BACKWARD, deltaTime);
    }
    if(key == PRESSED_LEFT) {
        m_Camera->ProcessKeyboard(LEFT, deltaTime);
    }
    if(key == PRESSED_RIGHT) {
        m_Camera->ProcessKeyboard(RIGHT, deltaTime);
    }
}
