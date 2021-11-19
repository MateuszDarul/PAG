#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "Transform.h"
#include "Shader.h"

class Drawable
{
protected:
    Transform transform;

public:
    Drawable();
    virtual ~Drawable();

    virtual void draw()=0;

    Transform* getTransform();
    virtual bool useTexture();
};

#endif // __DRAWABLE_H__
