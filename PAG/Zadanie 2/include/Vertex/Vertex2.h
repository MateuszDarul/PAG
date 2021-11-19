#ifndef __VERTEX2_H__
#define __VERTEX2_H__

#include "Vertex.h"


class Vertex2 : public Vertex
{
public:
    float x;
    float y;

    Vertex2(float x, float y);
    Vertex2();
    ~Vertex2();
    std::vector<float> toVector();
    void concat(std::vector<float> &target);
};

#endif // __VERTEX2_H__
