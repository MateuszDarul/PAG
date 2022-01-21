#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

class Transform
{
private:

public:
    glm::mat4 world_matrix;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform();
    ~Transform();

    glm::mat4 GetCombinedMatrix();
};

#endif // __TRANSFORM_H__
