#include "Shape.h"

void Shape::remake(unsigned int sector_count, unsigned int stack_count)
{
    ;
}

Shape::Shape()
{
    vertex_type = VertexType::Undefined;
    show_edges = false;
    use_texture = false;
    texture = nullptr;
}

Shape::~Shape()
{

}

void Shape::generate(VertexType vertex_type)
{
    if(vertex_type == VertexType::Undefined)
    {
        std::cerr << "You cant select [VertexType::Undefined] as vertex_type" << std::endl;
        exit(2);
    }

    this->vertex_type = vertex_type;

    vertex_list.clear();

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glGenBuffers(1, &vertex_buffer_objects);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_objects);
    glBufferData(GL_ARRAY_BUFFER, vertex_list.size() * sizeof(float), &vertex_list[0], GL_STATIC_DRAW);

    switch(this->vertex_type)
    {
    case VertexType::Position:
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    break;
    case VertexType::Position_Texture:
    {
        use_texture = true;

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    break;
    case VertexType::Position_Color:
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    break;
    case VertexType::Position_Color_Texture:
    {
        use_texture = true;

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    break;
    default:
        ;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Shape::draw()
{
    if(vertex_type == VertexType::Undefined)
    {
        std::cerr << "You must generate object before drawing" << std::endl;
        return;
    }

    if(show_edges)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(use_texture && texture != nullptr)
        texture->bindTexture();

    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, vertex_list.size()/vertex_type);

    texture->unbindTexture();
}

void Shape::remove()
{
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteBuffers(1, &vertex_buffer_objects);

    vertex_type = VertexType::Undefined;
    vertex_array_object = 0;
    vertex_buffer_objects = 0;
    vertex_list.clear();
}

bool Shape::addVertex(Vertex3 vertex)
{
    if(!addVertexTest(VertexType::Position))
        return false;

    vertex.concat(vertex_list);
    this->updateBuffor();
    return true;
}

bool Shape::addVertex(Vertex5 vertex)
{
    if(!addVertexTest(VertexType::Position_Texture))
        return false;

    vertex.concat(vertex_list);
    this->updateBuffor();
    return true;
}

bool Shape::addVertex(Vertex6 vertex)
{
    if(!addVertexTest(VertexType::Position_Color))
        return false;

    vertex.concat(vertex_list);
    this->updateBuffor();
    return true;
}

bool Shape::addVertex(Vertex8 vertex)
{
    if(!addVertexTest(VertexType::Position_Color_Texture))
        return false;

    vertex.concat(vertex_list);
    this->updateBuffor();
    return true;
}

void Shape::updateBuffor()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_objects);
    glBufferData(GL_ARRAY_BUFFER, vertex_list.size() * sizeof(float), &vertex_list[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool Shape::addVertexTest(VertexType used)
{
    if(vertex_type == VertexType::Undefined)
    {
        std::cerr << "You must generate object before adding vertex" << std::endl;
        return false;
    }

    if(vertex_type != used)
    {
        std::cerr << "Incorrect vertex type (you should use [Vertex::" << vertex_type << "])" <<  std::endl;
        return false;
    }

    return true;
}

bool Shape::setColor(int wall, Vertex3 color)
{
    if(vertex_type != VertexType::Position_Color && vertex_type != VertexType::Position_Color_Texture)
    {
        std::cerr << "You must generate Shape [VertexType::Position_Color] or [VertexType::Position_Color_Texture] to use this function" << std::endl;
        return false;
    }

    int walls_amount = (vertex_list.size()/(face_type*vertex_type))-1;
    if(wall > walls_amount)
    {
        std::cerr << "If you want fill all walls, use [-1] as wall arg, correct value of wall arg is in range [-1;" << (vertex_list.size()/(face_type*vertex_type))-1 << "]" << std::endl;
    }

    if(wall < 0 || wall > walls_amount)
    {
        for(unsigned int i=3; i<vertex_list.size(); i+=vertex_type)
        {
            vertex_list[i+0] = color.x;
            vertex_list[i+1] = color.y;
            vertex_list[i+2] = color.z;
        }
    }
    else
    {
        for(int i=wall*vertex_type*face_type+3; i<wall*vertex_type*face_type+face_type*vertex_type; i+=vertex_type)
        {
            vertex_list[i+0] = color.x;
            vertex_list[i+1] = color.y;
            vertex_list[i+2] = color.z;
        }
    }

    updateBuffor();

    return true;
}

void Shape::setDisplayMode(bool show_edges)
{
    this->show_edges = show_edges;
}

bool Shape::useTexture()
{
    return use_texture;
}

void Shape::setTexture(Texture* texture)
{
    this->texture = texture;
}

Texture* Shape::getTexture()
{
    if(texture == nullptr)
    {
        std::cerr << "This shape has not setting texture" << std::endl;
    }

    return texture;
}

void Shape::setOrigin(glm::vec3 origin)
{
    setOrigin(origin.x, origin.y, origin.z);
}

void Shape::setOrigin(Vertex3 origin)
{
    setOrigin(origin.x, origin.y, origin.z);
}

void Shape::setOrigin(float x, float y, float z)
{
    if(vertex_type == VertexType::Undefined)
    {
        std::cerr << "You must generate Shape before using this function" << std::endl;
        return;
    }

    for(int i=0; i<vertex_list.size(); i+=vertex_type)
    {
        vertex_list[i+0] -= x;
        vertex_list[i+1] -= y;
        vertex_list[i+2] -= z;
    }

    updateBuffor();
}
