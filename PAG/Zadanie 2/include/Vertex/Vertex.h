#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

class Vertex
{
public:
    Vertex();
    virtual ~Vertex();

    virtual std::vector<float> toVector()=0;
    virtual void concat(std::vector<float> &target)=0;
};

#include "Vertex2.h"
#include "Vertex3.h"
#include "Vertex5.h"
#include "Vertex6.h"
#include "Vertex8.h"

#endif // VERTEX_H
