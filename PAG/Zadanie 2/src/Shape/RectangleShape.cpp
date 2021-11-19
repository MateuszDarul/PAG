#include "RectangleShape.h"

RectangleShape::RectangleShape(float size_x, float size_y)
    :size_x(size_x/2), size_y(size_y/2)
{

}

RectangleShape::~RectangleShape()
{

}

void RectangleShape::make()
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

bool RectangleShape::setColor(int id_vert, Vertex3 color)
{
    if(id_vert == -2)
    {
        setColor(0, Vertex3(1, 0, 0));
        setColor(1, Vertex3(0, 1, 0));
        setColor(2, Vertex3(0, 0, 1));
        setColor(3, Vertex3(1, 1, 0));
        return true;
    }

    if(vertex_type != VertexType::Position_Color && vertex_type != VertexType::Position_Color_Texture)
    {
        std::cerr << "You must generate Shape [VertexType::Position_Color] or [VertexType::Position_Color_Texture] to use this function" << std::endl;
        return false;
    }

    if(id_vert < 0 || id_vert > 3)
    {
        if(id_vert > 3)
        {
            std::cerr << "If you want fill all vertex, use [-1] as wall arg, correct value of vertex arg is in range [-1;3]" << std::endl;
        }

        for(int i=0; i<vertex_list.size()/vertex_type; i++)
        {
            vertex_list[(vertex_type * i) + 3] = color.x;
            vertex_list[(vertex_type * i) + 4] = color.y;
            vertex_list[(vertex_type * i) + 5] = color.z;
        }
    }
    else
    {
        switch(id_vert)
        {
        case 0:
        {
            vertex_list[(vertex_type * 4) + 3] = color.x;
            vertex_list[(vertex_type * 4) + 4] = color.y;
            vertex_list[(vertex_type * 4) + 5] = color.z;
        }
        break;
        case 1:
        {
            vertex_list[(vertex_type * 0) + 3] = color.x;
            vertex_list[(vertex_type * 0) + 4] = color.y;
            vertex_list[(vertex_type * 0) + 5] = color.z;

            vertex_list[(vertex_type * 3) + 3] = color.x;
            vertex_list[(vertex_type * 3) + 4] = color.y;
            vertex_list[(vertex_type * 3) + 5] = color.z;
        }
        break;
        case 2:
        {
            vertex_list[(vertex_type * 2) + 3] = color.x;
            vertex_list[(vertex_type * 2) + 4] = color.y;
            vertex_list[(vertex_type * 2) + 5] = color.z;

            vertex_list[(vertex_type * 5) + 3] = color.x;
            vertex_list[(vertex_type * 5) + 4] = color.y;
            vertex_list[(vertex_type * 5) + 5] = color.z;
        }
        break;
        case 3:
        {
            vertex_list[(vertex_type * 1) + 3] = color.x;
            vertex_list[(vertex_type * 1) + 4] = color.y;
            vertex_list[(vertex_type * 1) + 5] = color.z;
        }
        break;
        }
    }

    updateBuffor();
}

///---

void RectangleShape::make_VT_Position()
{
    addVertex(Vertex3(size_x, size_y, 0));
    addVertex(Vertex3(size_x, -size_y, 0));
    addVertex(Vertex3(-size_x, -size_y, 0));

    addVertex(Vertex3(size_x, size_y, 0));
    addVertex(Vertex3(-size_x, size_y, 0));
    addVertex(Vertex3(-size_x, -size_y, 0));
}

void RectangleShape::make_VT_PositionColor()
{
    addVertex(Vertex6(size_x, size_y, 0, 1, 1, 1));
    addVertex(Vertex6(size_x, -size_y, 0, 1, 1, 1));
    addVertex(Vertex6(-size_x, -size_y, 0, 1, 1, 1));

    addVertex(Vertex6(size_x, size_y, 0, 1, 1, 1));
    addVertex(Vertex6(-size_x, size_y, 0, 1, 1, 1));
    addVertex(Vertex6(-size_x, -size_y, 0, 1, 1, 1));
}

void RectangleShape::make_VT_PositionTexture()
{
    addVertex(Vertex5(size_x, size_y, 0, 1, 1));
    addVertex(Vertex5(size_x, -size_y, 0, 1, 0));
    addVertex(Vertex5(-size_x, -size_y, 0, 0, 0));

    addVertex(Vertex5(size_x, size_y, 0, 1, 1));
    addVertex(Vertex5(-size_x, size_y, 0, 0, 1));
    addVertex(Vertex5(-size_x, -size_y, 0, 0, 0));
}

