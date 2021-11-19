#ifndef VERTEX_8_H
#define VERTEX_8_H

#include "Vertex.h"

class Vertex8 : public Vertex
{
public:
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    float s;
    float t;

    Vertex8(float x, float y, float z, float r, float g, float b, float s, float t);
    Vertex8();
    ~Vertex8();
    std::vector<float> toVector();
    void concat(std::vector<float> &target);
};

#endif // VERTEX_8_H
