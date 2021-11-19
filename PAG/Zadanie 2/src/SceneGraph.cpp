#include "SceneGraph.h"

SceneGraph::SceneGraph(Drawable* shape, Transform local_transform)
    :shape(shape), local_transform(local_transform)
{

}

SceneGraph::~SceneGraph()
{

}

SceneGraph* SceneGraph::getNode(Drawable* shape)
{
    for(unsigned int i=0; i<children.size(); i++)
    {
        if(children[i]->shape == shape)
        {
            return children[i];
        }
        else if(children[i]->getSize() > 0)
        {
            return getNode(shape);
        }
    }

    return nullptr;
}

SceneGraph* SceneGraph::getNode(unsigned int id)
{
    return children[id];
}

void SceneGraph::update()
{
    for(unsigned int i=0; i<children.size(); i++)
    {
        children[i]->getTransform()->set(local_transform.combine(*children[i]->getLocalTransform()));

        if(children[i]->getSize() > 0)
            children[i]->update();
    }
}

void SceneGraph::addChild(Drawable* shape)
{
    children.push_back(new SceneGraph(shape));
}

bool SceneGraph::removeChild(Drawable* shape)
{
    for(int i=0; i<children.size(); i++)
    {
        if(children[i]->getShape() == shape)
        {
            children.erase(children.begin() + i);
            return true;
        }
    }
    return false;
}

unsigned int SceneGraph::getSize()
{
    return children.size();
}

Transform* SceneGraph::getTransform()
{
    return &local_transform;
}

Transform* SceneGraph::getLocalTransform()
{
    return shape->getTransform();
}

Drawable* SceneGraph::getShape()
{
    return shape;
}

void SceneGraph::render(Shader* shader)
{
    shader->use();

    for(unsigned int i=0; i<children.size(); i++)
    {
        shader->setMat4("transform", children[i]->getTransform()->getTransformations());
        shader->setBool("use_texture", children[i]->getShape()->useTexture());

        children[i]->getShape()->draw();

        if(children[i]->getSize() > 0)
            children[i]->render(shader);
    }
}
