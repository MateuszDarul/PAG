#include "Cube.h"

Cube::Cube(float size)
    :Shape(), size(size/2)
{
    face_type = FaceType::Square;
}

Cube::~Cube()
{

}

void Cube::make()
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



///--------------------------------------------------------------------------------------------------------------

void Cube::make_VT_Position()
{
    /// front
    addVertex(Vertex3(size, size, size));
    addVertex(Vertex3(size, -size, size));
    addVertex(Vertex3(-size, -size, size));

    addVertex(Vertex3(size, size, size));
    addVertex(Vertex3(-size, size, size));
    addVertex(Vertex3(-size, -size, size));

    /// back
    addVertex(Vertex3(size, size, -size));
    addVertex(Vertex3(size, -size, -size));
    addVertex(Vertex3(-size, -size, -size));

    addVertex(Vertex3(size, size, -size));
    addVertex(Vertex3(-size, size, -size));
    addVertex(Vertex3(-size, -size, -size));

    /// up
    addVertex(Vertex3(size, size, -size));
    addVertex(Vertex3(size, size, size));
    addVertex(Vertex3(-size, size, size));

    addVertex(Vertex3(size, size, -size));
    addVertex(Vertex3(-size, size, -size));
    addVertex(Vertex3(-size, size, size));

    /// down
    addVertex(Vertex3(size, -size, -size));
    addVertex(Vertex3(size, -size, size));
    addVertex(Vertex3(-size, -size, size));

    addVertex(Vertex3(size, -size, -size));
    addVertex(Vertex3(-size, -size, -size));
    addVertex(Vertex3(-size, -size, size));

    /// left
    addVertex(Vertex3(-size, size, size));
    addVertex(Vertex3(-size, -size, size));
    addVertex(Vertex3(-size, -size, -size));

    addVertex(Vertex3(-size, size, size));
    addVertex(Vertex3(-size, size, -size));
    addVertex(Vertex3(-size, -size, -size));

    /// right
    addVertex(Vertex3(size, size, size));
    addVertex(Vertex3(size, -size, size));
    addVertex(Vertex3(size, -size, -size));

    addVertex(Vertex3(size, size, size));
    addVertex(Vertex3(size, size, -size));
    addVertex(Vertex3(size, -size, -size));
}

void Cube::make_VT_PositionColor()
{
    /// front
    addVertex(Vertex6(size, size, size, 0, 1, 1));
    addVertex(Vertex6(size, -size, size, 0, 1, 1));
    addVertex(Vertex6(-size, -size, size, 0, 1, 1));

    addVertex(Vertex6(size, size, size, 0, 1, 1));
    addVertex(Vertex6(-size, size, size, 0, 1, 1));
    addVertex(Vertex6(-size, -size, size, 0, 1, 1));

    /// back
    addVertex(Vertex6(size, size, -size, 1, 1, 1));
    addVertex(Vertex6(size, -size, -size, 1, 1, 1));
    addVertex(Vertex6(-size, -size, -size, 1, 1, 1));

    addVertex(Vertex6(size, size, -size, 1, 1, 1));
    addVertex(Vertex6(-size, size, -size, 1, 1, 1));
    addVertex(Vertex6(-size, -size, -size, 1, 1, 1));

    /// up
    addVertex(Vertex6(size, size, -size, 1, 0, 0));
    addVertex(Vertex6(size, size, size, 1, 0, 0));
    addVertex(Vertex6(-size, size, size, 1, 0, 0));

    addVertex(Vertex6(size, size, -size, 1, 0, 0));
    addVertex(Vertex6(-size, size, -size, 1, 0, 0));
    addVertex(Vertex6(-size, size, size, 1, 0, 0));

    /// down
    addVertex(Vertex6(size, -size, -size, 0, 1, 0));
    addVertex(Vertex6(size, -size, size, 0, 1, 0));
    addVertex(Vertex6(-size, -size, size, 0, 1, 0));

    addVertex(Vertex6(size, -size, -size, 0, 1, 0));
    addVertex(Vertex6(-size, -size, -size, 0, 1, 0));
    addVertex(Vertex6(-size, -size, size, 0, 1, 0));

    /// left
    addVertex(Vertex6(-size, size, size, 0, 0, 1));
    addVertex(Vertex6(-size, -size, size, 0, 0, 1));
    addVertex(Vertex6(-size, -size, -size, 0, 0, 1));

    addVertex(Vertex6(-size, size, size, 0, 0, 1));
    addVertex(Vertex6(-size, size, -size, 0, 0, 1));
    addVertex(Vertex6(-size, -size, -size, 0, 0, 1));

    /// right
    addVertex(Vertex6(size, size, size, 1, 1, 0));
    addVertex(Vertex6(size, -size, size, 1, 1, 0));
    addVertex(Vertex6(size, -size, -size, 1, 1, 0));

    addVertex(Vertex6(size, size, size, 1, 1, 0));
    addVertex(Vertex6(size, size, -size, 1, 1, 0));
    addVertex(Vertex6(size, -size, -size, 1, 1, 0));
}

void Cube::make_VT_PositionTexture()
{
    /// front
    addVertex(Vertex5(size, size, size, 1, 1));
    addVertex(Vertex5(size, -size, size, 1, 0));
    addVertex(Vertex5(-size, -size, size, 0, 0));

    addVertex(Vertex5(size, size, size, 1, 1));
    addVertex(Vertex5(-size, size, size, 0, 1));
    addVertex(Vertex5(-size, -size, size, 0, 0));

    /// back
    addVertex(Vertex5(size, size, -size, 1, 1));
    addVertex(Vertex5(size, -size, -size, 1, 0));
    addVertex(Vertex5(-size, -size, -size, 0, 0));

    addVertex(Vertex5(size, size, -size, 1, 1));
    addVertex(Vertex5(-size, size, -size, 0, 1));
    addVertex(Vertex5(-size, -size, -size, 0, 0));

    /// up
    addVertex(Vertex5(size, size, -size, 1, 0));
    addVertex(Vertex5(size, size, size, 1, 1));
    addVertex(Vertex5(-size, size, size, 0, 1));

    addVertex(Vertex5(size, size, -size, 1, 0));
    addVertex(Vertex5(-size, size, -size, 0, 0));
    addVertex(Vertex5(-size, size, size, 0, 1));

    /// down
    addVertex(Vertex5(size, -size, -size, 1, 0));
    addVertex(Vertex5(size, -size, size, 1, 1));
    addVertex(Vertex5(-size, -size, size, 0, 1));

    addVertex(Vertex5(size, -size, -size, 1, 0));
    addVertex(Vertex5(-size, -size, -size, 0, 0));
    addVertex(Vertex5(-size, -size, size, 0, 1));

    /// left
    addVertex(Vertex5(-size, size, size, 1, 1));
    addVertex(Vertex5(-size, -size, size, 0, 1));
    addVertex(Vertex5(-size, -size, -size, 0, 0));

    addVertex(Vertex5(-size, size, size, 1, 1));
    addVertex(Vertex5(-size, size, -size, 1, 0));
    addVertex(Vertex5(-size, -size, -size, 0, 0));

    /// right
    addVertex(Vertex5(size, size, size, 1, 1));
    addVertex(Vertex5(size, -size, size, 0, 1));
    addVertex(Vertex5(size, -size, -size, 0, 0));

    addVertex(Vertex5(size, size, size, 1, 1));
    addVertex(Vertex5(size, size, -size, 1, 0));
    addVertex(Vertex5(size, -size, -size, 0, 0));
}
