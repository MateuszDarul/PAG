#include "Tetraedr.h"

Tetraedr::Tetraedr(float size)
    :Shape(), size(size/2)
{
    face_type = FaceType::Triangle;
}

Tetraedr::~Tetraedr()
{

}

void Tetraedr::make()
{
    switch(vertex_type)
    {
    case VertexType::Position:
    {
        make_VT_Position();
    }
    break;
    case VertexType::Position_Color:
    {
        make_VT_PositionColor();
    }
    break;
    case VertexType::Position_Texture:
    {
        make_VT_PositionTexture();
    }
    break;

    default:
        std::cerr << "This vertex type is not supported yet. [" << vertex_type << "]" << std::endl;
        exit(1);
    }
}

void Tetraedr::make_VT_Position()
{
    addVertex(Vertex3(size,  size,  size));
    addVertex(Vertex3(-size, -size,  size));
    addVertex(Vertex3(-size,  size, -size));

    addVertex(Vertex3(size,  size,  size));
    addVertex(Vertex3(-size, -size,  size));
    addVertex(Vertex3(size, -size, -size));

    addVertex(Vertex3(size,  size,  size));
    addVertex(Vertex3(-size,  size, -size));
    addVertex(Vertex3(size, -size, -size));

    addVertex(Vertex3(-size, -size,  size));
    addVertex(Vertex3(-size,  size, -size));
    addVertex(Vertex3(size, -size, -size));
}

void Tetraedr::make_VT_PositionColor()
{
    addVertex(Vertex6(size,  size,  size, 0, 0, 0));
    addVertex(Vertex6(-size, -size,  size, 0, 0, 0));
    addVertex(Vertex6(-size,  size, -size, 0, 0, 0));

    addVertex(Vertex6(size,  size,  size, 1, 0, 0));
    addVertex(Vertex6(-size, -size,  size, 1, 0, 0));
    addVertex(Vertex6(size, -size, -size, 1, 0, 0));

    addVertex(Vertex6(size,  size,  size, 0, 1, 0));
    addVertex(Vertex6(-size,  size, -size, 0, 1, 0));
    addVertex(Vertex6(size, -size, -size, 0, 1, 0));

    addVertex(Vertex6(-size, -size,  size, 0, 0, 1));
    addVertex(Vertex6(-size,  size, -size, 0, 0, 1));
    addVertex(Vertex6(size, -size, -size, 0, 0, 1));
}

void Tetraedr::make_VT_PositionTexture()
{
    addVertex(Vertex5(size,  size,  size, 1, 1));
    addVertex(Vertex5(-size, -size,  size, 0, 1));
    addVertex(Vertex5(-size,  size, -size, 0, 0));

    addVertex(Vertex5(size,  size,  size, 1, 1));
    addVertex(Vertex5(-size, -size,  size, 0, 1));
    addVertex(Vertex5(size, -size, -size, 0, 0));

    addVertex(Vertex5(size,  size,  size, 1, 1));
    addVertex(Vertex5(-size,  size, -size, 0, 1));
    addVertex(Vertex5(size, -size, -size, 0, 0));

    addVertex(Vertex5(-size, -size,  size, 1, 1));
    addVertex(Vertex5(-size,  size, -size, 0, 1));
    addVertex(Vertex5(size, -size, -size, 0, 0));
}
