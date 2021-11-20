#include "Circle.h"

Circle::Circle(float radius, float thickness, float precision)
    :radius(radius), thickness(thickness), precision(precision)
{
    face_type = FaceType::Line;
}

Circle::~Circle()
{

}

void Circle::draw()
{
    if(vertex_type == VertexType::Undefined)
    {
        std::cerr << "You must generate object before drawing" << std::endl;
        return;
    }

    if(use_texture && texture != nullptr)
        texture->bindTexture();

    glLineWidth(thickness);

    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_LINE_STRIP, 0, vertex_list.size()/vertex_type);

    glLineWidth(1);

    texture->unbindTexture();
}

void Circle::make()
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

void Circle::make_VT_Position()
{
    float angle = 0;
    for(angle=0; angle<=(2*M_PI)+precision; angle+=precision)
    {
        float x = radius * sin(angle);
        float y = radius * cos(angle);

        addVertex(Vertex3(x, y, 0));
    }
}

void Circle::make_VT_PositionColor()
{
    float angle = 0;
    for(angle=0; angle<=(2*M_PI)+precision; angle+=precision)
    {
        float x = radius * sin(angle);
        float y = radius * cos(angle);

        addVertex(Vertex6(x, y, 0, 1, 1, 1));
    }
}

void Circle::make_VT_PositionTexture()
{
    float angle = 0;
    for(angle=0; angle<=(2*M_PI)+precision; angle+=precision)
    {
        float x = sin(angle);
        float y = cos(angle);

        addVertex(Vertex5(radius*x, radius*y, 0, x, y));
    }
}
