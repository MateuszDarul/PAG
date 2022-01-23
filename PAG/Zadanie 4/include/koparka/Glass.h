#ifndef __GLASS_H__
#define __GLASS_H__

#include "RenderObject.h"


class Glass : public RenderObject
{
private:
    unsigned int* cubemap_texture;
    unsigned int VAO;
    unsigned int VBO;

public:
    Glass(unsigned int* cubemap_texture);

    void Create(Shader* shader, float size_x, float size_y, float size_z, float offset_x=0, float offset_y=0, float offset_z=0);
    void Draw();
};

#endif // __GLASS_H__
