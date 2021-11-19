#include "Line.h"

Line::Line(float thickness)
{

}

Line::~Line()
{

}

void Line::draw()
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

void Line::make()
{
    ;
}
