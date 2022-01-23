#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "RenderObject.h"

class Floor : public RenderObject
{
private:
    unsigned int TEX;
    int width, height, nrChannels;
    unsigned char *data;

    unsigned int VAO;
    unsigned int VBO;

public:
    Floor();
    ~Floor();

    void Create(Shader* shader, float size_x, float size_y, float size_z, float offset_x=0, float offset_y=0, float offset_z=0);
    void Draw();
};

#endif // __FLOOR_H__
