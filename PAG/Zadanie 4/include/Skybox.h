#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "RenderObject.h"

#include <vector>

class Skybox : public RenderObject
{
private:
    unsigned int cubemap_texture;
    unsigned int VAO;
    unsigned int VBO;

public:
    Skybox();
    void Create(Shader* shader, float size_x, float size_y, float size_z, float offset_x=0, float offset_y=0, float offset_z=0);
    void Draw();

    unsigned int* GetSkyboxTexture();
};

#endif // __SKYBOX_H__
