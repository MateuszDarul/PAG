#include "Vertex6.h"

Vertex6::Vertex6(float x, float y, float z, float r, float g, float b)
    :x(x), y(y), z(z), r(r), g(g), b(b)
{

}

Vertex6::Vertex6()
{

}

Vertex6::~Vertex6()
{

}

std::vector<float> Vertex6::toVector()
{
    std::vector<float> tmp;
    tmp.insert(tmp.end(), {x, y, z, r, g, b});
    return tmp;
}

void Vertex6::concat(std::vector<float> &target)
{
    target.insert(target.end(), {x, y, z, r, g, b});
}
