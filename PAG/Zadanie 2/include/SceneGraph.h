#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__

#include "Drawable.h"
#include "Transform.h"
#include "Shader.h"

class SceneGraph
{
private:
    Drawable* shape;
    Transform local_transform;
    std::vector<SceneGraph*> children;

public:
    SceneGraph(Drawable* shape, Transform local_transform=Transform());
    ~SceneGraph();

    void update();

    void addChild(Drawable* shape);
    bool removeChild(Drawable* shape);

    SceneGraph* getNode(Drawable* shape);
    SceneGraph* getNode(unsigned int id);

    unsigned int getSize();

    Transform* getTransform();
    Transform* getLocalTransform();

    Drawable* getShape();

    void render(Shader* shader);
};
#endif // __SCENEGRAPH_H__
