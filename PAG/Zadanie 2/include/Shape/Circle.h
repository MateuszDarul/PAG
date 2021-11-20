#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Shape.h"


class Circle : public Shape
{
private:
    float thickness;
    float radius;
    float precision;

private:
    void make_VT_Position();
    void make_VT_PositionColor();
    void make_VT_PositionTexture();

public:
    Circle(float radius, float thickness = 1, float precision = 0.05);
    ~Circle();

    void draw();
    void make();
};

#endif // __CIRCLE_H__
