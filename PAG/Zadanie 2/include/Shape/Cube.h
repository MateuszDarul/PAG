#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"


class Cube : public Shape
{
private:
    float size;

private:
    void make_VT_Position();
    void make_VT_PositionColor();
    void make_VT_PositionTexture();

public:
    Cube(float size);
    ~Cube();

    void make();
};

#endif // CUBE_H
