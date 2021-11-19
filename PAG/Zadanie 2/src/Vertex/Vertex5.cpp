#include "Vertex5.h"

Vertex5::Vertex5(float x, float y, float z, float s, float t)
    :x(x), y(y), z(z), s(s), t(t)
{

}

Vertex5::Vertex5()
{

}

Vertex5::~Vertex5()
{

}

std::vector<float> Vertex5::toVector()
{
    std::vector<float> tmp;
    tmp.insert(tmp.end(), {x, y, z, s, t});
    return tmp;
}

void Vertex5::concat(std::vector<float> &target)
{
    target.insert(target.end(), {x, y, z, s, t});
}
