#include "Transform.h"

Transform::Transform()
{
    model_matrix = glm::mat4(1.f);
    view_matrix = glm::mat4(1.f);
    projection_matrix = glm::mat4(1.f);

    position_matrix = glm::mat4(1.f);
    rotation_matrix = glm::mat4(1.f);
    scale_matrix = glm::mat4(1.f);
}

Transform::~Transform()
{

}

void Transform::set(Transform transform)
{
    this->model_matrix = transform.getModel();
    this->view_matrix = transform.getView();
    this->projection_matrix = transform.getProjection();
}

Transform Transform::Origin()
{
    Transform origin;
    return origin;
}

void Transform::setModel(glm::mat4 model_matrix)
{
    this->model_matrix = model_matrix;
}

void Transform::setView(glm::mat4 view_matrix)
{
    this->view_matrix = view_matrix;
}

void Transform::setProjection(glm::mat4 projection_matrix)
{
    this->projection_matrix = projection_matrix;
}

glm::mat4 Transform::getModel()
{
    return model_matrix;
}

glm::mat4 Transform::getView()
{
    return view_matrix;
}

glm::mat4 Transform::getProjection()
{
    return projection_matrix;
}

glm::mat4 Transform::getTransformations()
{
    return projection_matrix * view_matrix * model_matrix;
}

void Transform::resetModel()
{
    model_matrix = glm::mat4(1.f);
}

void Transform::resetView()
{
    view_matrix = glm::mat4(1.f);
}

void Transform::resetProjection()
{
    projection_matrix = glm::mat4(1.f);
}

Transform Transform::combine(Transform& transform)
{
     Transform result;

     result.setModel(this->getModel() * transform.getModel());
     result.setView(this->getView() * transform.getView());
     result.setProjection(this->getProjection() * transform.getProjection());

     return result;
}

void Transform::setPosition(float x, float y, float z)
{
    position_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    setModel(position_matrix * rotation_matrix * scale_matrix);
}

void Transform::move(float x, float y, float z)
{
    position_matrix = glm::translate(position_matrix, glm::vec3(x, y, z));
    setModel(position_matrix * rotation_matrix * scale_matrix);
}

void Transform::setRotation(float degrees, float x, float y, float z)
{
    rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::vec3(x, y, z));
    setModel(position_matrix * rotation_matrix * scale_matrix);
}

void Transform::rotate(float degrees, float x, float y, float z)
{
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(degrees), glm::vec3(x, y, z));
    setModel(position_matrix * rotation_matrix * scale_matrix);
}
void Transform::setScale(float x, float y, float z)
{
    scale_matrix = glm::scale(glm::mat4(1.f), glm::vec3(x, y, z));
    setModel(position_matrix * rotation_matrix * scale_matrix);
}

void Transform::scale(float x, float y, float z)
{
    scale_matrix = glm::scale(scale_matrix, glm::vec3(x, y, z));
    setModel(position_matrix * rotation_matrix * scale_matrix);
}

void Transform::setPosition(glm::vec3 position)
{
    setPosition(position.x, position.y, position.z);
}

void Transform::setPosition(Vertex3 position)
{
    setPosition(position.x, position.y, position.z);
}

void Transform::move(glm::vec3 vector)
{
    move(vector.x, vector.y, vector.z);
}

void Transform::move(Vertex3 vector)
{
    move(vector.x, vector.y, vector.z);
}

void Transform::setRotation(float degrees, glm::vec3 axes)
{
    setRotation(degrees, axes.x, axes.y, axes.z);
}

void Transform::setRotation(float degrees, Vertex3 axes)
{
    setRotation(degrees, axes.x, axes.y, axes.z);
}

void Transform::rotate(float degrees, glm::vec3 axes)
{
    setRotation(degrees, axes.x, axes.y, axes.z);
}

void Transform::rotate(float degrees, Vertex3 axes)
{
    setRotation(degrees, axes.x, axes.y, axes.z);
}

void Transform::setScale(glm::vec3 scale)
{
    setScale(scale.x, scale.y, scale.z);
}

void Transform::setScale(Vertex3 scale)
{
    setScale(scale.x, scale.y, scale.z);
}

void Transform::scale(glm::vec3 scale)
{
    this->scale(scale.x, scale.y, scale.z);
}

void Transform::scale(Vertex3 scale)
{
    this->scale(scale.x, scale.y, scale.z);
}
