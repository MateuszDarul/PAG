#ifndef __OWNSHAPE_H__
#define __OWNSHAPE_H__

#include "Shape.h"

class OwnShape : public Shape
{
private:
    float size;

public:
    OwnShape(float size);
    ~OwnShape();

    void make();
};

#endif // __OWNSHAPE_H__
