#ifndef __TETRAEDR_H__
#define __TETRAEDR_H__

#include "Shape.h"


class Tetraedr : public Shape
{
private:
    float size;

private:
    void make_VT_Position();
    void make_VT_PositionColor();
    void make_VT_PositionTexture();

public:
    Tetraedr(float size);
    ~Tetraedr();

    void make();
};

#endif // __TETRAEDR_H__
