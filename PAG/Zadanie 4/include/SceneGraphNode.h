#ifndef __SCENEGRAPHNODE_H__
#define __SCENEGRAPHNODE_H__

#include <memory>
#include <vector>

#include "Transform.h"
#include "Shader.h"

#include "RenderObject.h"

class SceneGraphNode
{
public:
    bool dirty;
    std::vector<std::shared_ptr<SceneGraphNode>> children;
    std::shared_ptr<RenderObject> obj;
    Transform transform;

public:
    SceneGraphNode();
    SceneGraphNode(std::shared_ptr<RenderObject>& obj);
    explicit SceneGraphNode(const Transform& transform);
    ~SceneGraphNode();

    void AddChild(const std::shared_ptr<SceneGraphNode>& object);

    void Update(const Transform& parent_transform, bool dirty_);
    void UpdateTransform();
    void Render(bool is_root=false);

    Transform& GetTransform();
};

#endif // __SCENEGRAPHNODE_H__
