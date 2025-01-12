#include "Chessboard.h"

Chessboard::Chessboard() : m_X(4), m_Y(4)
{
}

Chessboard::~Chessboard()
{
}

void Chessboard::UpdateDimensions(unsigned int x, unsigned int y) {
    this->m_X = x;
    this->m_Y = y;
}
