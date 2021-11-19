#ifndef VERTEX_3_H
#define VERTEX_3_H

#include "Vertex.h"

class Vertex3 : public Vertex
{
public:
    float x;
    float y;
    float z;

    Vertex3(float x, float y, float z);
    Vertex3();
    ~Vertex3();
    std::vector<float> toVector();
    void concat(std::vector<float> &target);
};

#endif // VERTEX_3_H
