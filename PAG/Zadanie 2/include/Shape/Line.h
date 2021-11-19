#ifndef __LINE_H__
#define __LINE_H__

#include "Shape.h"

class Line : public Shape
{
private:
    float thickness;

public:
    Line(float thickness);
    ~Line();
    void draw();
    void make();

};

#endif // __LINE_H__
