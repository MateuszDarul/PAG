#include "Vertex3.h"

Vertex3::Vertex3(float x, float y, float z)
    :x(x), y(y), z(z)
{

}

Vertex3::Vertex3()
{

}

Vertex3::~Vertex3()
{

}

std::vector<float> Vertex3::toVector()
{
    std::vector<float> tmp;
    tmp.insert(tmp.end(), {x, y, z});
    return tmp;
}

void Vertex3::concat(std::vector<float> &target)
{
    target.insert(target.end(), {x, y, z});
}
