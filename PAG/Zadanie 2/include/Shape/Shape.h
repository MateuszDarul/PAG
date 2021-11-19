#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>
#include <iostream>
#include <cmath>

#include <glad/glad.h>

#include "Vertex.h"
#include "Texture.h"

#include "Drawable.h"

enum VertexType
{
    Undefined = 0,
    Position = 3,
    Position_Texture = 5,
    Position_Color = 6,
    Position_Color_Texture = 8
};

enum FaceType
{
    Undef = 0,
    Triangle = 3,
    Square = 6
};

class Shape : public Drawable
{
protected:
    bool show_edges;
    FaceType face_type;

    VertexType vertex_type;
    unsigned int vertex_array_object;
    unsigned int vertex_buffer_objects;

    std::vector<float> vertex_list;

    bool use_texture;
    Texture* texture;

protected:
    void updateBuffor();
    bool addVertexTest(VertexType used);

public:
    Shape();
    virtual ~Shape();

    void generate(VertexType vertex_type);
    virtual void make()=0;
    void remove();
    virtual void draw();

    /** Fill shape selected color
     * @param wall      [-1] fill all walls
     *                  [0 - {amoumt of walls}-1] fill selected wall
     * @param color     color to fill walls
     */
    virtual bool setColor(int wall, Vertex3 color);

    void setTexture(Texture* texture);
    Texture* getTexture();

    void setDisplayMode(bool show_edges);

    bool addVertex(Vertex3 v3);
    bool addVertex(Vertex5 v5);
    bool addVertex(Vertex6 v6);
    bool addVertex(Vertex8 v8);

    bool useTexture();

    void setOrigin(Vertex3 origin);
    void setOrigin(glm::vec3 origin);
    void setOrigin(float x, float y, float z);



    virtual void remake(unsigned int sector_count, unsigned int stack_count);  ///Do usuniecia
};


#include "Cube.h"
#include "Tetraedr.h"
#include "Sphere.h"
#include "OwnShape.h"

#include "Line.h"
#include "Circle.h"
#include "RectangleShape.h"
#include "CircleShape.h"

#endif // __SHAPE_H__
