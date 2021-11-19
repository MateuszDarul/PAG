#include "Vertex2.h"

Vertex2::Vertex2(float x, float y)
    :x(x), y(y)
{

}

Vertex2::Vertex2()
{

}

Vertex2::~Vertex2()
{

}

std::vector<float> Vertex2::toVector()
{
    std::vector<float> tmp;
    tmp.insert(tmp.end(), {x, y});
    return tmp;
}

void Vertex2::concat(std::vector<float> &target)
{
    target.insert(target.end(), {x, y});
}
