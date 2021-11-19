#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Shape.h"

class Sphere : public Shape
{
private:
    float radius;
    unsigned int sector_count;
    unsigned int stack_count;

private:
    void make_VT_Position();
    void make_VT_PositionColor();
    void make_VT_PositionTexture();

public:
    Sphere(float radius, unsigned int sector_count, unsigned int stack_count);
    ~Sphere();

    void make();


    void remake(unsigned int sector_count, unsigned int stack_count);
};

#endif // __SPHERE_H__
