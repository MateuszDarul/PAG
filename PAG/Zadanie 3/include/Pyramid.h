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
    glm::vec3 *transformations;

    Pyramid(glm::vec3 *transformations);
    ~Pyramid();

    void Create(Shader* shader, float size_x, float size_y, float size_z);
    void Draw();
};


#endif // PYRAMID_H
