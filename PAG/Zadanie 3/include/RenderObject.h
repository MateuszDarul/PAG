#ifndef __RENDEROBJECT_H__
#define __RENDEROBJECT_H__

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

class RenderObject
{
public:
    RenderObject();
    virtual ~RenderObject();
    virtual void Create(float x, float y, float z)=0;
    virtual void Draw()=0;
};

#include "Floor.h"
#include "Cube.h"

#endif // __RENDEROBJECT_H__
