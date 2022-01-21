#ifndef __RENDEROBJECT_H__
#define __RENDEROBJECT_H__

#include <iostream>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include "Shader.h"

#define ilosc_instancji 200

class RenderObject
{
protected:
    Shader* shader;
    glm::mat4 transform;

public:
    RenderObject();
    virtual ~RenderObject();
    virtual void Create(Shader* shader, float size_x, float size_y, float size_z)=0;
    virtual void Draw()=0;
    void setTransform(glm::mat4 transform);
};

#include "Floor.h"
#include "Cube.h"
#include "Pyramid.h"
#include "LightMark.h"

#include "Skybox.h"

#include "Mirror.h"

#endif // __RENDEROBJECT_H__
