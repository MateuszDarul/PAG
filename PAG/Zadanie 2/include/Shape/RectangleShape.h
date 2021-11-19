#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Shape.h"


class RectangleShape : public Shape
{
private:
    float size_x;
    float size_y;

    void make_VT_Position();
    void make_VT_PositionColor();
    void make_VT_PositionTexture();

public:
    RectangleShape(float size_x, float size_y);
    ~RectangleShape();

    bool setColor(int id_vert, Vertex3 color);

    void make();
};

#endif // __RECTANGLE_H__
