#include "RenderObject.h"

RenderObject::RenderObject()
{
    //ctor
}

RenderObject::~RenderObject()
{
    //dtor
}

void RenderObject::setTransform(glm::mat4 transform)
{
    this->transform = transform;
}

