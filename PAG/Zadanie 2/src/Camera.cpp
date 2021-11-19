#include "Camera.h"

Camera::Camera(glm::vec3 position)
    :position(position)
{
    target = glm::vec3(0,0,0);
}

void Camera::setPosition(float x, float y, float z)
{
    setPosition(glm::vec3(x, y, z));
}

void Camera::setPosition(glm::vec3 position)
{
    this->position = position;
}

void Camera::move(float x, float y, float z)
{
    move(glm::vec3(x, y, z));
}

void Camera::move(glm::vec3 position)
{
    this->position.x += position.x;
    this->position.y += position.y;
    this->position.z += position.z;
}

glm::mat4 Camera::getView()
{
    return glm::lookAt(position, target, glm::vec3(0,1,0));
}
