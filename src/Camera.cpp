#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

const float SPEED =  0.5f;

Camera::Camera(unsigned int windowWidth, unsigned int windowHeight) : m_Position(glm::vec3(0.0f, 0.05f, 3.0f)), m_Front(glm::vec3(0.0f, 0.05f, -1.0f)), m_Up(glm::vec3(0.0f, 0.1f, 0.0f))
{
    this->m_WindowWidth = windowWidth;
    this->m_WindowHeigt = windowHeight;
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(m_Position, m_Front, m_Up);
}

glm::mat4 Camera::GetProjectionMatrix() {
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float) this->m_WindowWidth / (float) this->m_WindowHeigt, 0.1f, 100.0f);
    return projection;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = SPEED * deltaTime;
    if (direction == FORWARD)
        m_Position += glm::vec3(0.0f, 0.0f, -1.0f) * velocity;
    if (direction == BACKWARD)
        m_Position -= glm::vec3(0.0f, 0.0f, -1.0f) * velocity;
    if(direction == LEFT) {
        m_Position += glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
        m_Front += glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
    }
    if(direction == RIGHT) {
        m_Position -= glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
        m_Front -= glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
    }
    
}

void Camera::UpdateWindowSize(unsigned int width, unsigned int height) {
    this->m_WindowWidth = width;
    this->m_WindowHeigt = height;
}
