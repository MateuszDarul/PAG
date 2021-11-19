#ifndef VERTEX_5_H
#define VERTEX_5_H

#include "Vertex.h"

class Vertex5 : public Vertex
{
public:
    float x;
    float y;
    float z;
    float s;
    float t;

    Vertex5(float x, float y, float z, float s, float t);
    Vertex5();
    ~Vertex5();
    std::vector<float> toVector();
    void concat(std::vector<float> &target);
};

#endif // VERTEX_5_H
