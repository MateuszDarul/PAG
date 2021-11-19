#include "UkladPlanet.h"

UkladPlanet::UkladPlanet(int window_size_x, int window_size_y)
    :window_size_x(window_size_x), window_size_y(window_size_y)
{
    sphere_quality = 20;
    show_grid = false;
    obrot_x = false;
    obrot_y = false;
    obrot_z = false;



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

    orbita_2 = new Circle(1);
    orbita_2->generate(VertexType::Position_Color);
    orbita_2->make();
    orbita_2->getTransform()->setPosition(2, 0, 0);
    scene_graph->getNode(orbita_1)->addChild(orbita_2);

    ksiezyc_1 = new Tetraedr(0.25);
    ksiezyc_1->generate(VertexType::Position_Color);
    ksiezyc_1->make();
    ksiezyc_1->getTransform()->setPosition(1, 0, 0);
    scene_graph->getNode(orbita_1)->getNode(orbita_2)->addChild(ksiezyc_1);

}

UkladPlanet::~UkladPlanet()
{
    delete scene_graph;


    slonce->remove();
    orbita_1->remove();
    planeta_1->remove();
    delete slonce;
    delete orbita_1;
    delete planeta_1;


    delete camera;
    delete shader;
}

void UkladPlanet::loop()
{
    if(obrot_x)
        scene_graph->getTransform()->rotate(1, 1, 0, 0);
    if(obrot_y)
        scene_graph->getTransform()->rotate(1, 0, 1, 0);
    if(obrot_z)
        scene_graph->getTransform()->rotate(1, 0, 0, 1);

    slonce->getTransform()->rotate(0.5,0,0,1);
    orbita_1->getTransform()->rotate(1,0,0,1);
    {
        planeta_1->getTransform()->rotate(-2,0,0,1);
        orbita_2->getTransform()->rotate(1,0,0,1);
        {
            ksiezyc_1->getTransform()->rotate(-4,0,0,1);
        }
    }

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
    if(ImGui::Button("Show grid"))
    {
        show_grid = !show_grid;

        slonce->setDisplayMode(show_grid);
        planeta_1->setDisplayMode(show_grid);
        ksiezyc_1->setDisplayMode(show_grid);
    }
    ImGui::Checkbox("X", &obrot_x);
    ImGui::SameLine();
    ImGui::Checkbox("Y", &obrot_y);
    ImGui::SameLine();
    ImGui::Checkbox("Z", &obrot_z);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 0.001*ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
