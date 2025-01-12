#pragma once

class Chessboard
{
public:
    Chessboard();
    ~Chessboard();
    
    inline unsigned int GetX() { return m_X; };
    inline unsigned int GetY() { return  m_Y; };
    
    void UpdateDimensions(unsigned int x, unsigned int y);

private:
    unsigned int m_X;
    unsigned int m_Y;
};
