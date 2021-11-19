#include "CircleShape.h"

CircleShape::CircleShape(float radius, float precision)
    :radius(radius), precision(precision)
{

}

CircleShape::~CircleShape()
{

}

void CircleShape::make()
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

bool CircleShape::setColor(int id_vert, Vertex3 color)
{
    if(vertex_type != VertexType::Position_Color && vertex_type != VertexType::Position_Color_Texture)
    {
        std::cerr << "You must generate Shape [VertexType::Position_Color] or [VertexType::Position_Color_Texture] to use this function" << std::endl;
        return false;
    }

    if(id_vert < 0)
    {
        for(int i=0; i<vertex_list.size()/vertex_type; i++)
        {
            vertex_list[(vertex_type * i) + 3] = color.x;
            vertex_list[(vertex_type * i) + 4] = color.y;
            vertex_list[(vertex_type * i) + 5] = color.z;
        }
    }
    else
    {
        vertex_list[(vertex_type * id_vert) + 3] = color.x;
        vertex_list[(vertex_type * id_vert) + 4] = color.y;
        vertex_list[(vertex_type * id_vert) + 5] = color.z;
    }

    updateBuffor();
}

///---

void CircleShape::make_VT_Position()
{
    float old_x = radius * sin(0);
    float old_y = radius * cos(0);

    float x = radius * sin(precision);
    float y = radius * cos(precision);

    float angle = 0;
    for(angle=precision; angle<=(2*M_PI)+precision; angle+=precision)
    {
        float x = radius * sin(angle);
        float y = radius * cos(angle);

        addVertex(Vertex3(old_x, old_y, 0));
        addVertex(Vertex3(0, 0, 0));
        addVertex(Vertex3(x, y, 0));

        old_x = x;
        old_y = y;
    }
}

void CircleShape::make_VT_PositionColor()
{
    float old_x = radius * sin(0);
    float old_y = radius * cos(0);

    float x = radius * sin(precision);
    float y = radius * cos(precision);

    float angle = 0;
    int i=0;
    for(angle=precision; angle<=(2*M_PI)+precision; angle+=precision)
    {
        float x = radius * sin(angle);
        float y = radius * cos(angle);

        addVertex(Vertex6(old_x, old_y, 0, 1, 1, 1));
        addVertex(Vertex6(0, 0, 0, 1, 1, 1));
        addVertex(Vertex6(x, y, 0, 1, 1, 1));

        old_x = x;
        old_y = y;
    }
}

void CircleShape::make_VT_PositionTexture()
{
    float old_x = sin(0);
    float old_y = cos(0);

    float x = sin(precision);
    float y = cos(precision);

    float angle = 0;
    for(angle=precision; angle<=(2*M_PI)+precision; angle+=precision)
    {
        float x = sin(angle);
        float y = cos(angle);

        addVertex(Vertex5(old_x, old_y, 0, (old_x*0.5)+0.5, (old_y*0.5)+0.5));
        addVertex(Vertex5(0, 0, 0, 0.5, 0.5));
        addVertex(Vertex5(x, y, 0, (x*0.5)+0.5, (y*0.5)+0.5));

        old_x = x;
        old_y = y;
    }
}

