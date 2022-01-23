#ifndef __KOPARKA_H__
#define __KOPARKA_H__

#include <memory>

#include "RenderObject.h"
#include "SceneGraphNode.h"

class Koparka
{
private:
    std::vector<std::shared_ptr<SceneGraphNode>> nodes;
    float kola, kolo;

public:
    Koparka(std::shared_ptr<SceneGraphNode> parent_node, Shader* shader_list[], Skybox* skybox);

    void Kolo(int id, float kat);
    void Kola(float kat);
    void Oska(float kat);
    void Ramie(int id, float kat);
    void Szufla(float kat);
    void Move(glm::vec3 offset);
    std::shared_ptr<SceneGraphNode> GetNode(int id);
};

#endif // __KOPARKA_H__
