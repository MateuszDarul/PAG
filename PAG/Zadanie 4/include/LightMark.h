#ifndef LIGHTMARK_H
#define LIGHTMARK_H

#include "RenderObject.h"


class LightMark : public RenderObject
{
private:
    unsigned int TEX;
    int width, height, nrChannels;
    unsigned char *data;

    unsigned int VAO;
    unsigned int VBO;

public:
    LightMark();
    ~LightMark();

    void Create(Shader* shader, float size_x, float size_y, float size_z);
    void Draw();
};

#endif // LIGHTMARK_H
