#pragma once

#include <glm/glm.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(unsigned int windowWidth, unsigned int windowHeight);
    ~Camera();
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void UpdateWindowSize(unsigned int width, unsigned int height);

private:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    unsigned int m_WindowWidth;
    unsigned int m_WindowHeigt;
};
