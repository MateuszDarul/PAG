#ifndef __CIRCLESHAPE_H__
#define __CIRCLESHAPE_H__

#include "Shape.h"

class CircleShape : public Shape
{
private:
    float radius;
    float precision;

    void make_VT_Position();
    void make_VT_PositionColor();
    void make_VT_PositionTexture();

public:
    CircleShape(float radius, float precision = 0.05);
    ~CircleShape();

    bool setColor(int id_vert, Vertex3 color);

    void make();
};

#endif // __CIRCLESHAPE_H__
