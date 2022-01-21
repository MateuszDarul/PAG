#ifndef __MIRROR_H__
#define __MIRROR_H__

#include "RenderObject.h"


class Glass : public RenderObject
{
private:
    unsigned int* cubemap_texture;
    unsigned int VAO;
    unsigned int VBO;

public:
    Glass(unsigned int* cubemap_texture);

    void Create(Shader* shader, float size_x, float size_y, float size_z);
    void Draw();
};

#endif // __MIRROR_H__
