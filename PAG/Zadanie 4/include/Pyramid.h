#ifndef PYRAMID_H
#define PYRAMID_H

#include "RenderObject.h"

class Pyramid : public RenderObject
{
private:
    unsigned int TEX;
    int width, height, nrChannels;
    unsigned char *data;

    unsigned int VAO;
    unsigned int VBO;

public:
    unsigned int instanceVBO;
    glm::mat4 *transformations;

    Pyramid(glm::mat4 *transformations);
    ~Pyramid();

    void Create(Shader* shader, float size_x, float size_y, float size_z, float offset_x=0, float offset_y=0, float offset_z=0);
    void Draw();
};


#endif // PYRAMID_H
