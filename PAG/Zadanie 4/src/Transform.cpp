#include "Transform.h"

Transform::Transform()
    :world_matrix(1.f)
{
    position = glm::vec3(0,0,0);
    rotation = glm::vec3(0,0,0);
    scale = glm::vec3(1,1,1);
}

Transform::~Transform()
{

}

glm::mat4 Transform::GetCombinedMatrix()
{
    return
        glm::translate(glm::mat4(1.f), position)*
        glm::rotate(glm::mat4(1.f), glm::radians(rotation.z), glm::vec3(0,0,1))*
        glm::rotate(glm::mat4(1.f), glm::radians(rotation.y), glm::vec3(0,1,0))*
        glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), glm::vec3(1,0,0))*
        glm::scale(glm::mat4(1.f), glm::vec3(scale));
}
