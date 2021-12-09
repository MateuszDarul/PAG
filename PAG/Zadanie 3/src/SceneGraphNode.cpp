#include "SceneGraphNode.h"

SceneGraphNode::SceneGraphNode()
    :dirty(true)
{
    obj = nullptr;
    transform.world_matrix = glm::mat4(1.f);
}

SceneGraphNode::SceneGraphNode(std::shared_ptr<RenderObject>& obj)
    :dirty(true), obj(obj)
{
    transform.world_matrix = glm::mat4(1.f);
}

SceneGraphNode::SceneGraphNode(const Transform& transform)
    :dirty(true), transform(transform)
{

}

SceneGraphNode::~SceneGraphNode()
{

}

void SceneGraphNode::AddChild(const std::shared_ptr<SceneGraphNode>& object)
{
    children.push_back(object);
}

void SceneGraphNode::Update(const Transform& parent_transform, bool dirty_)
{
    dirty_ |= dirty;

    if(dirty_)
    {
        transform.world_matrix = transform.GetCombinedMatrix();
        transform.world_matrix = parent_transform.world_matrix * transform.world_matrix;
        dirty = false;
    }

    for(unsigned short int i=0; i<children.size(); i++)
    {
        children[i]->Update(parent_transform, dirty_);
    }
}

void SceneGraphNode::UpdateTransform()
{
    transform.world_matrix = transform.GetCombinedMatrix();
    dirty = true;
}

void SceneGraphNode::Render(Shader& shader, bool is_root)
{
    if(!is_root)
    {
        shader.use();
        shader.setBool("use_texture", true);
        shader.setMat4("transformations", transform.world_matrix);
        obj->Draw();
    }

    for(unsigned short int i=0; i<children.size(); i++)
    {
        children[i]->Render(shader);
    }
}

Transform& SceneGraphNode::GetTransform()
{
    dirty = true;
    return transform;
}
