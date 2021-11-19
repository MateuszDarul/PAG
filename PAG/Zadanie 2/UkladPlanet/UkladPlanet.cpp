#include "UkladPlanet.h"

UkladPlanet::UkladPlanet(int window_size_x, int window_size_y)
    :window_size_x(window_size_x), window_size_y(window_size_y)
{
    sphere_quality = 20;
    show_grid = false;



    shader = new Shader("resources/shaders/vertexShader.vert", "resources/shaders/fragmentShader.frag");
    scene_graph = new SceneGraph(nullptr);
    camera = new Camera(glm::vec3(0, 0, 10));

    scene_graph->getTransform()->setView(camera->getView());
    scene_graph->getTransform()->setProjection
            (glm::perspective(glm::radians(90.0f), (float)window_size_x/(float)window_size_y, 0.1f, 100.0f));


    slonce = new Sphere(1, sphere_quality, sphere_quality);
    slonce->generate(VertexType::Position_Color);
    slonce->make();
    scene_graph->addChild(slonce);

    orbita_1 = new Circle(2);
    orbita_1->generate(VertexType::Position_Color);
    orbita_1->make();
    scene_graph->addChild(orbita_1);

    planeta_1 = new Cube(0.5);
    planeta_1->generate(VertexType::Position_Color);
    planeta_1->make();
    planeta_1->getTransform()->setPosition(2, 0, 0);
    scene_graph->getNode(orbita_1)->addChild(planeta_1);

    orbita_5 = new Circle(1);
    orbita_5->generate(VertexType::Position_Color);
    orbita_5->make();
    orbita_5->getTransform()->setPosition(2, 0, 0);
    scene_graph->getNode(orbita_1)->addChild(orbita_5);

    ksiezyc_1 = new Sphere(0.25, 5, 5);
    ksiezyc_1->generate(VertexType::Position_Color);
    ksiezyc_1->make();
    ksiezyc_1->getTransform()->setPosition(1, 0, 0);
    scene_graph->getNode(orbita_1)->getNode(orbita_5)->addChild(ksiezyc_1);
}

UkladPlanet::~UkladPlanet()
{
    delete scene_graph;


    slonce->remove();
    orbita_1->remove();
    planeta_1->remove();
    orbita_5->remove();
    ksiezyc_1->remove();
    delete slonce;
    delete orbita_1;
    delete planeta_1;
    delete orbita_5;
    delete ksiezyc_1;


    delete camera;
    delete shader;
}

void UkladPlanet::loop()
{
    if(show_grid)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(obrot_x)
        scene_graph->getTransform()->rotate(1, 1, 0, 0);
    if(obrot_y)
        scene_graph->getTransform()->rotate(1, 0, 1, 0);
    if(obrot_z)
        scene_graph->getTransform()->rotate(1, 0, 0, 1);




    scene_graph->update();
    scene_graph->render(shader);
}

void UkladPlanet::gui()
{
    ImGui::Begin("GUI");
    //ImGui::SliderFloat("zoom", &zoom, -50.f, 50.f);
    if(ImGui::Button("-"))
    {
        if(sphere_quality > 3)
        {
            sphere_quality--;
            slonce->remake(sphere_quality, sphere_quality);
        }
    }
    ImGui::SameLine();
    if(ImGui::Button("+"))
    {
        sphere_quality++;
        slonce->remake(sphere_quality, sphere_quality);
    }
    ImGui::SameLine();
    ImGui::Text("Sphere quality (%d)", sphere_quality);
    ImGui::Checkbox("Show grid", &show_grid);

    ImGui::Checkbox("X", &obrot_x);
    ImGui::SameLine();
    ImGui::Checkbox("Y", &obrot_y);
    ImGui::SameLine();
    ImGui::Checkbox("Z", &obrot_z);
    ImGui::End();
}
