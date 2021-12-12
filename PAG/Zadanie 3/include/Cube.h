#ifndef __CUBE_H__
#define __CUBE_H__

#include "RenderObject.h"

class Cube : public RenderObject
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

    Cube(glm::vec3 *transformations);
    ~Cube();

    void Create(Shader* shader, float size_x, float size_y, float size_z);
    void Draw();
};

#endif // __CUBE_H__
