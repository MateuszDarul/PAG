#include "Koparka.h"

Koparka::Koparka(std::shared_ptr<SceneGraphNode> parent_node, Shader* shader_list[], Skybox* skybox)
{
    int szer = 5;
    int dlug = 10;

    /// Podwozie
    std::shared_ptr<RenderObject> box = std::make_shared<Box>();
    box->Create(shader_list[0], 1.5*szer, 2, 2*dlug);
    std::shared_ptr<SceneGraphNode> box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(0, 5, 100);
    parent_node->AddChild(box_node);
    nodes.push_back(box_node);

    /// Kola
    box = std::make_shared<Box>();
    box->Create(shader_list[0], 2, 5, 5);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(-szer, -2.5, -dlug);
    nodes[0]->AddChild(box_node);
    nodes.push_back(box_node);
    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().rotation += glm::vec3(45, 0, 0);
    nodes[1]->AddChild(box_node);
    nodes.push_back(box_node);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(szer, -2.5, -dlug);
    nodes[0]->AddChild(box_node);
    nodes.push_back(box_node);
    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().rotation += glm::vec3(45, 0, 0);
    nodes[3]->AddChild(box_node);
    nodes.push_back(box_node);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(-szer, -2.5, dlug);
    nodes[0]->AddChild(box_node);
    nodes.push_back(box_node);
    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().rotation += glm::vec3(45, 0, 0);
    nodes[5]->AddChild(box_node);
    nodes.push_back(box_node);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(szer, -2.5, dlug);
    nodes[0]->AddChild(box_node);
    nodes.push_back(box_node);
    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().rotation += glm::vec3(45, 0, 0);
    nodes[7]->AddChild(box_node);
    nodes.push_back(box_node);

    /// Os
    box = std::make_shared<Box>();
    box->Create(shader_list[0], 2.5, 1, 2.5);
    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(0, 1.5, 0);
    nodes[0]->AddChild(box_node);
    nodes.push_back(box_node);

    /// Podstawa kabiny
    box = std::make_shared<Box>();
    box->Create(shader_list[0], 5, 0.5, 15);
    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(-2.5, 0.75, 0);
    nodes[9]->AddChild(box_node);
    nodes.push_back(box_node);


    /// Dach kabiny
    box = std::make_shared<Box>();
    box->Create(shader_list[0], 5, 0.5, 8.5);
    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(0, 5, -3.25);
    nodes[10]->AddChild(box_node);
    nodes.push_back(box_node);

    /// Tyl kabiny
    box = std::make_shared<Mirror>(skybox->GetSkyboxTexture());
    box->Create(shader_list[1], 5, 0.5, 7.5);
    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(0, 2.5, 3.25);
    box_node->GetTransform().rotation += glm::vec3(45, 0, 0);
    nodes[10]->AddChild(box_node);
    nodes.push_back(box_node);

    /// Podpory kabiny
    box = std::make_shared<Box>();
    box->Create(shader_list[0], 0.5, 5, 0.5);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(2.5, 2.5, -7.5);
    nodes[10]->AddChild(box_node);
    nodes.push_back(box_node);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(-2.5, 2.5, -7.5);
    nodes[10]->AddChild(box_node);
    nodes.push_back(box_node);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(2.5, 2.5, 0);
    nodes[10]->AddChild(box_node);
    nodes.push_back(box_node);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(-2.5, 2.5, 0);
    nodes[10]->AddChild(box_node);
    nodes.push_back(box_node);

    /// Ramie pierwsze
    box = std::make_shared<Box>();
    box->Create(shader_list[0], 1.5, 20, 1.5, 0, 10, 0);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(1, 0, 0);
    //box_node->GetTransform().rotation += glm::vec3(-45, 0, 0);
    nodes[9]->AddChild(box_node);
    nodes.push_back(box_node);


    /// Ramie drugie
    box = std::make_shared<Box>();
    box->Create(shader_list[0], 1.5, 15, 1.5, 0, 7.5, 0);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(0.5, 19, 0);
    //box_node->GetTransform().rotation += glm::vec3(-45, 0, 0);
    nodes[17]->AddChild(box_node);
    nodes.push_back(box_node);

    /// Szufla
    box = std::make_shared<Box>();
    box->Create(shader_list[0], 3, 2, 5, 0, 0, -2.5);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(0, 15, 0);
    //box_node->GetTransform().rotation += glm::vec3(-45, 0, 0);
    nodes[18]->AddChild(box_node);
    nodes.push_back(box_node);


    /// Szyba
    box = std::make_shared<Glass>(skybox->GetSkyboxTexture());
    box->Create(shader_list[2], 5, 5, 1);

    box_node = std::make_shared<SceneGraphNode>(box);
    box_node->GetTransform().position += glm::vec3(0, 2.5, -7.5);
    nodes[10]->AddChild(box_node);
    nodes.push_back(box_node);

}

void Koparka::Kolo(int id, float kat)
{
    kolo = kat;
    switch(id)
    {
    case 0:
        {
            nodes[1]->GetTransform().rotation = glm::vec3(kat, kola, 0);
        }
        break;
    case 1:
        {
            nodes[3]->GetTransform().rotation = glm::vec3(kat, kola, 0);
        }
        break;
    case 2:
        {
            nodes[5]->GetTransform().rotation = glm::vec3(kat, 0, 0);
        }
        break;
    case 3:
        {
            nodes[7]->GetTransform().rotation = glm::vec3(kat, 0, 0);
        }
        break;
    }
}

void Koparka::Kola(float kat)
{
    kola = kat;
    nodes[1]->GetTransform().rotation = glm::vec3(kolo, kat, 0);
    nodes[3]->GetTransform().rotation = glm::vec3(kolo, kat, 0);
}

void Koparka::Oska(float kat)
{
    nodes[9]->GetTransform().rotation = glm::vec3(0, kat, 0);
}

void Koparka::Ramie(int id, float kat)
{
    switch(id)
    {
    case 0:
        {
            nodes[17]->GetTransform().rotation = glm::vec3(kat, 0, 0);
        }
        break;
    case 1:
        {
            nodes[18]->GetTransform().rotation = glm::vec3(kat, 0, 0);
        }
        break;
    }
}

void Koparka::Szufla(float kat)
{
    nodes[19]->GetTransform().rotation = glm::vec3(kat, 0, 0);
}

void Koparka::Move(glm::vec3 offset)
{
    nodes[0]->GetTransform().position += offset;
}

std::shared_ptr<SceneGraphNode> Koparka::GetNode(int id)
{
    return nodes[id];
}
