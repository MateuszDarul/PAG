#include "Sphere.h"

void Sphere::remake(unsigned int sector_count, unsigned int stack_count)
{
    vertex_list.clear();
    this->sector_count = sector_count;
    this->stack_count = stack_count;
    make();
}

Sphere::Sphere(float radius, unsigned int sector_count, unsigned int stack_count)
    :Shape(), radius(radius/2), sector_count(sector_count), stack_count(stack_count)
{
    if(sector_count < 4 || stack_count < 4)
    {
        std::cerr << "Arg [sector_count], and [sector_count] must be larger or equal [4]" << std::endl;
        sector_count = 4;
        stack_count = 4;
    }

    face_type = FaceType::Triangle;
}

Sphere::~Sphere()
{

}

void Sphere::make()
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

void Sphere::make_VT_Position()
{
    std::vector<Vertex3> ver;

    float x, y, z, xy;

    float sector_step = 2 * M_PI / sector_count;
    float stack_step = M_PI / stack_count;

    float sector_angle;
    float stack_angle;

    for(int i=0; i<=stack_count; i++)
    {
        stack_angle = M_PI / 2 - i * stack_step;
        xy = radius * cosf(stack_angle);
        z = radius * sinf(stack_angle);

        for(int j=0; j<=sector_count; j++)
        {
            sector_angle = j * sector_step;

            x = xy * cosf(sector_angle);
            y = xy * sinf(sector_angle);
            ver.push_back(Vertex3(x, y, z));
        }
    }

    std::vector<int> ind;
    int k1, k2;
    for(int i=0; i<stack_count; i++)
    {
        k1 = i * (sector_count + 1);
        k2 = k1 + sector_count + 1;

        for(int j=0; j<sector_count; j++, k1++, k2++)
        {
            if(i != 0)
            {
                ind.push_back(k1);
                ind.push_back(k2);
                ind.push_back(k1+1);
            }

            if(i != (stack_count-1))
            {
                ind.push_back(k1+1);
                ind.push_back(k2);
                ind.push_back(k2+1);
            }
        }
    }

    for(int i=0; i<ind.size(); i+=3)
    {
        addVertex(Vertex3(ver[ind[i+0]]));
        addVertex(Vertex3(ver[ind[i+1]]));
        addVertex(Vertex3(ver[ind[i+2]]));
    }
}

void Sphere::make_VT_PositionColor()
{
    std::vector<Vertex3> ver;

    float x, y, z, xy;

    float sector_step = 2 * M_PI / sector_count;
    float stack_step = M_PI / stack_count;

    float sector_angle;
    float stack_angle;

    for(int i=0; i<=stack_count; i++)
    {
        stack_angle = M_PI / 2 - i * stack_step;
        xy = radius * cosf(stack_angle);
        z = radius * sinf(stack_angle);

        for(int j=0; j<=sector_count; j++)
        {
            sector_angle = j * sector_step;

            x = xy * cosf(sector_angle);
            y = xy * sinf(sector_angle);
            ver.push_back(Vertex3(x, y, z));
        }
    }

    std::vector<int> ind;
    int k1, k2;
    for(int i=0; i<stack_count; i++)
    {
        k1 = i * (sector_count + 1);
        k2 = k1 + sector_count + 1;

        for(int j=0; j<sector_count; j++, k1++, k2++)
        {
            if(i != 0)
            {
                ind.push_back(k1);
                ind.push_back(k2);
                ind.push_back(k1+1);
            }

            if(i != (stack_count-1))
            {
                ind.push_back(k1+1);
                ind.push_back(k2);
                ind.push_back(k2+1);
            }
        }
    }

    int add = 1;
    float gray = 0;
    for(int i=0; i<ind.size(); i+=3)
    {
        addVertex(Vertex6(ver[ind[i+0]].x, ver[ind[i+0]].y, ver[ind[i+0]].z, gray, gray, gray));
        addVertex(Vertex6(ver[ind[i+1]].x, ver[ind[i+1]].y, ver[ind[i+1]].z, gray, gray, gray));
        addVertex(Vertex6(ver[ind[i+2]].x, ver[ind[i+2]].y, ver[ind[i+2]].z, gray, gray, gray));

        gray += add*0.1;
        if(gray > 1)
        {
            add = -1;
            gray = 1;
        }
        else if(gray < 0)
        {
            add = 1;
            gray = 0;
        }
    }
}

void Sphere::make_VT_PositionTexture()
{
    std::vector<Vertex5> ver;

    float x, y, z, xy;
    float s, t;

    float sector_step = 2 * M_PI / sector_count;
    float stack_step = M_PI / stack_count;

    float sector_angle;
    float stack_angle;

    for(int i=0; i<=stack_count; i++)
    {
        stack_angle = M_PI / 2 - i * stack_step;
        xy = radius * cosf(stack_angle);
        z = radius * sinf(stack_angle);

        for(int j=0; j<=sector_count; j++)
        {
            sector_angle = j * sector_step;

            x = xy * cosf(sector_angle);
            y = xy * sinf(sector_angle);

            s = (float)j / sector_count;
            t = (float)i / stack_count;

            ver.push_back(Vertex5(x, y, z, s, t));
        }
    }

    std::vector<int> ind;
    int k1, k2;
    for(int i=0; i<stack_count; i++)
    {
        k1 = i * (sector_count + 1);
        k2 = k1 + sector_count + 1;

        for(int j=0; j<sector_count; j++, k1++, k2++)
        {
            if(i != 0)
            {
                ind.push_back(k1);
                ind.push_back(k2);
                ind.push_back(k1+1);
            }

            if(i != (stack_count-1))
            {
                ind.push_back(k1+1);
                ind.push_back(k2);
                ind.push_back(k2+1);
            }
        }
    }

    for(int i=0; i<ind.size(); i+=5)
    {
        addVertex(Vertex5(ver[ind[i+0]]));
        addVertex(Vertex5(ver[ind[i+1]]));
        addVertex(Vertex5(ver[ind[i+2]]));
        addVertex(Vertex5(ver[ind[i+3]]));
        addVertex(Vertex5(ver[ind[i+4]]));
    }
}
