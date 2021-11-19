#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include "Vertex.h"

class Transform
{
private:
    glm::mat4 model_matrix;
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;

    glm::mat4 position_matrix;
    glm::mat4 rotation_matrix;
    glm::mat4 scale_matrix;

public:
    Transform();
    ~Transform();

    void set(Transform transform);

    glm::mat4 getModel();
    glm::mat4 getView();
    glm::mat4 getProjection();

    void setModel(glm::mat4 model_matrix);
    void setView(glm::mat4 view_matrix);
    void setProjection(glm::mat4 projection_matrix);

    void resetModel();
    void resetView();
    void resetProjection();

    void setScale(glm::vec3 scale);
    void setScale(Vertex3 scale);
    void setScale(float x, float y, float z);
    void scale(glm::vec3 scale);
    void scale(Vertex3 scale);
    void scale(float x, float y, float z);

    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);
    void setPosition(Vertex3 position);
    void move(float x, float y, float z);
    void move(glm::vec3 vector);
    void move(Vertex3 vector);

    void setRotation(float degrees, float x, float y, float z);
    void setRotation(float degrees, glm::vec3 axes);
    void setRotation(float degrees, Vertex3 axes);
    void rotate(float degrees, float x, float y, float z);
    void rotate(float degrees, glm::vec3 axes);
    void rotate(float degrees, Vertex3 axes);

    glm::mat4 getTransformations();

    Transform combine(Transform& transform);

    static Transform Origin();
};

#endif // TRANSFORM_H
