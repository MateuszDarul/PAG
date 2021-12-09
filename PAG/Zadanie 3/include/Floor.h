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

    void Create(float size_x, float size_y, float size_z);
    void Draw();
};

#endif // __FLOOR_H__
