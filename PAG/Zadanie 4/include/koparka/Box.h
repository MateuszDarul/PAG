#ifndef __BOX_H__
#define __BOX_H__

#include "RenderObject.h"

class Box : public RenderObject
{
private:
    std::string texture_name;
    unsigned int TEX;
    int width, height, nrChannels;
    unsigned char *data;

    unsigned int VAO;
    unsigned int VBO;

public:
    Box(std::string texture_name="resources/textures/None.jpg");

    void Create(Shader* shader, float size_x, float size_y, float size_z, float offset_x=0, float offset_y=0, float offset_z=0);
    void Draw();
};

#endif // __BOX_H__
