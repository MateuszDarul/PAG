#include "Vertex8.h"

Vertex8::Vertex8(float x, float y, float z, float r, float g, float b, float s, float t)
    :x(x), y(y), z(z), r(r), g(g), b(b), s(s), t(t)
{

}

Vertex8::Vertex8()
{

}

Vertex8::~Vertex8()
{

}

std::vector<float> Vertex8::toVector()
{
    std::vector<float> tmp;
    tmp.insert(tmp.end(), {x, y, z, r, g, b, s, t});
    return tmp;
}

void Vertex8::concat(std::vector<float> &target)
{
    target.insert(target.end(), {x, y, z, r, g, b, s, t});
}
