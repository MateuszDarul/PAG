#ifndef CAMERA_H
#define CAMERA_H

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 target;

public:
    Camera(glm::vec3 position);

    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);
    void move(float x, float y, float z);
    void move(glm::vec3 position);

    glm::mat4 getView();
};

#endif // CAMERA_H
