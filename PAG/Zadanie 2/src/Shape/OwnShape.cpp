#include "OwnShape.h"

OwnShape::OwnShape(float size)
    :Shape(), size(size)
{
    face_type = FaceType::Undef;
}

OwnShape::~OwnShape()
{

}

void OwnShape::make()
{

}
