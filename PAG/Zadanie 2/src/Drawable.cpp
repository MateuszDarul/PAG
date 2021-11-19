#include "Drawable.h"

Drawable::Drawable()
{

}

Drawable::~Drawable()
{

}

Transform* Drawable::getTransform()
{
    return &transform;
}

bool Drawable::useTexture()
{
    return true;
}
