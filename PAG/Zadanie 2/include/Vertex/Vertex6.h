#ifndef VERTEX_6_H
#define VERTEX_6_H

#include "Vertex.h"

class Vertex6 : public Vertex
{
public:
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;

    Vertex6(float x, float y, float z, float r, float g, float b);
    Vertex6();
    ~Vertex6();
    std::vector<float> toVector();
    void concat(std::vector<float> &target);
};

#endif // VERTEX_6_H
