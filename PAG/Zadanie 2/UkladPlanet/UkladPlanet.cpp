#include "UkladPlanet.h"

UkladPlanet::UkladPlanet(int window_size_x, int window_size_y)
    :window_size_x(window_size_x), window_size_y(window_size_y)
{
    sphere_quality = 20;
    show_grid = false;
    obrot_x = false;
    obrot_y = false;
    obrot_z = false;
    zoom = 15;

    shader = new Shader("resources/shaders/vertexShader.vert", "resources/shaders/fragmentShader.frag");
    scene_graph = new SceneGraph(nullptr);
    camera = new Camera(glm::vec3(0, 0, zoom));

    scene_graph->getTransform()->setView(camera->getView());
    scene_graph->getTransform()->setProjection
            (glm::perspective(glm::radians(90.0f), (float)window_size_x/(float)window_size_y, 0.1f, 100.0f));

    texture_1 = new Texture();
    texture_1->loadFromFile("resources/textures/Sphere.jpg");

    ///------------------------------------------------------------------
    slonce = new Sphere(1, sphere_quality, sphere_quality);
    slonce->generate(VertexType::Position_Color);
    slonce->make();
    scene_graph->addChild(slonce);

    ///------------------------------------------------------------------
    orbita_1 = new Circle(1.75);
    orbita_1->generate(VertexType::Position_Color);
    orbita_1->make();
    orbita_1->getTransform()->setRotation(30, 0, 1, 0);
    scene_graph->addChild(orbita_1);

    planeta_1 = new Cube(0.5);
    planeta_1->generate(VertexType::Position_Color);
    planeta_1->make();
    planeta_1->getTransform()->setPosition(1.75, 0, 0);
    scene_graph->getNode(1)->addChild(planeta_1);

    orbita_2 = new Circle(0.75);
    orbita_2->generate(VertexType::Position_Color);
    orbita_2->make();
    orbita_2->getTransform()->setPosition(1.75, 0, 0);
    scene_graph->getNode(1)->addChild(orbita_2);

    ksiezyc_1 = new Tetraedr(0.25);
    ksiezyc_1->generate(VertexType::Position_Color);
    ksiezyc_1->make();
    ksiezyc_1->getTransform()->setPosition(0.75, 0, 0);
    scene_graph->getNode(1)->getNode(1)->addChild(ksiezyc_1);

    ///------------------------------------------------------------------
    orbita_3 = new Circle(5);
    orbita_3->generate(VertexType::Position_Color);
    orbita_3->make();
    orbita_3->getTransform()->setRotation(60, 0, 1, 0);
    scene_graph->addChild(orbita_3);

    planeta_2 = new Tetraedr(1.25);
    planeta_2->generate(VertexType::Position_Color);
    planeta_2->make();
    planeta_2->getTransform()->setPosition(5, 0, 0);
    scene_graph->getNode(2)->addChild(planeta_2);

    orbita_4 = new Circle(1.5);
    orbita_4->generate(VertexType::Position_Color);
    orbita_4->make();
    orbita_4->getTransform()->setPosition(5, 0, 0);
    orbita_4->getTransform()->setRotation(30, 0, 1, 0);
    scene_graph->getNode(2)->addChild(orbita_4);

    ksiezyc_2 = new Cube(0.25);
    ksiezyc_2->generate(VertexType::Position_Color);
    ksiezyc_2->make();
    ksiezyc_2->getTransform()->setPosition(1.5, 0, 0);
    scene_graph->getNode(2)->getNode(1)->addChild(ksiezyc_2);

    orbita_5 = new Circle(2);
    orbita_5->generate(VertexType::Position_Color);
    orbita_5->make();
    orbita_5->getTransform()->setPosition(5, 0, 0);
    orbita_5->getTransform()->setRotation(60, 0, 1, 0);
    scene_graph->getNode(2)->addChild(orbita_5);

    ksiezyc_3 = new Sphere(0.5, 8, 8);
    ksiezyc_3->generate(VertexType::Position_Color);
    ksiezyc_3->make();
    ksiezyc_3->getTransform()->setPosition(2, 0, 0);
    scene_graph->getNode(2)->getNode(2)->addChild(ksiezyc_3);

    ///------------------------------------------------------------------
    orbita_6 = new Circle(8);
    orbita_6->generate(VertexType::Position_Color);
    orbita_6->make();
    orbita_6->getTransform()->setRotation(90, 0, 1, 0);
    scene_graph->addChild(orbita_6);

    planeta_3 = new Model("resources/models/lot/lot.obj", shader);
    planeta_3->getTransform()->setScale(0.25, 0.25, 0.25);
    planeta_3->getTransform()->setPosition(8, 0, 0);
    planeta_3->getTransform()->setRotation(180, 1, 1, 0);
    scene_graph->getNode(3)->addChild(planeta_3);

    orbita_7 = new Circle(1);
    orbita_7->generate(VertexType::Position_Color);
    orbita_7->make();
    orbita_7->getTransform()->setPosition(8, 0, 0);
    orbita_7->getTransform()->setRotation(90, 1, 0, 0);
    scene_graph->getNode(3)->addChild(orbita_7);

    ksiezyc_4 = new Model("resources/models/lot/lot.obj", shader);
    ksiezyc_4->getTransform()->setScale(0.1, 0.1, 0.1);
    ksiezyc_4->getTransform()->setPosition(1, 0, 0);
    ksiezyc_4->getTransform()->setRotation(180, 1, 1, 0);
    scene_graph->getNode(3)->getNode(1)->addChild(ksiezyc_4);

    ///------------------------------------------------------------------
    orbita_8 = new Circle(11);
    orbita_8->generate(VertexType::Position_Color);
    orbita_8->make();
    orbita_8->getTransform()->setRotation(45, 0, 1, 0);
    scene_graph->addChild(orbita_8);

    planeta_4 = new Sphere(2, 10, 10);
    planeta_4->generate(VertexType::Position_Texture);
    planeta_4->make();
    planeta_4->setTexture(texture_1);
    planeta_4->getTransform()->setPosition(11, 0, 0);
    scene_graph->getNode(4)->addChild(planeta_4);

    orbita_9 = new Circle(2.5);
    orbita_9->generate(VertexType::Position_Color);
    orbita_9->make();
    orbita_9->getTransform()->setPosition(11, 0, 0);
    scene_graph->getNode(4)->addChild(orbita_9);

    ksiezyc_5 = new Sphere(0.4, 8, 8);
    ksiezyc_5->generate(VertexType::Position_Color);
    ksiezyc_5->make();
    ksiezyc_5->getTransform()->setPosition(2.5, 0, 0);
    scene_graph->getNode(4)->getNode(1)->addChild(ksiezyc_5);

    orbita_10 = new Circle(2.5);
    orbita_10->generate(VertexType::Position_Color);
    orbita_10->make();
    orbita_10->getTransform()->setPosition(11, 0, 0);
    orbita_10->getTransform()->setRotation(60, 0, 1, 0);
    scene_graph->getNode(4)->addChild(orbita_10);

    ksiezyc_6 = new Sphere(0.4, 8, 8);
    ksiezyc_6->generate(VertexType::Position_Color);
    ksiezyc_6->make();
    ksiezyc_6->getTransform()->setPosition(0, 2.5, 0);
    scene_graph->getNode(4)->getNode(2)->addChild(ksiezyc_6);

    orbita_11 = new Circle(2.5);
    orbita_11->generate(VertexType::Position_Color);
    orbita_11->make();
    orbita_11->getTransform()->setPosition(11, 0, 0);
    orbita_11->getTransform()->setRotation(120, 0, 1, 0);
    scene_graph->getNode(4)->addChild(orbita_11);

    ksiezyc_7 = new Sphere(0.4, 8, 8);
    ksiezyc_7->generate(VertexType::Position_Color);
    ksiezyc_7->make();
    ksiezyc_7->getTransform()->setPosition(0, -2.5, 0);
    scene_graph->getNode(4)->getNode(3)->addChild(ksiezyc_7);
}

UkladPlanet::~UkladPlanet()
{
    delete scene_graph;

    delete texture_1;

    delete slonce;
    delete orbita_1;
    delete planeta_1;
    delete orbita_2;
    delete ksiezyc_1;
    delete orbita_3;
    delete planeta_2;
    delete orbita_4;
    delete ksiezyc_2;
    delete orbita_5;
    delete ksiezyc_3;
    delete orbita_6;
    delete planeta_3;
    delete orbita_7;
    delete ksiezyc_4;
    delete orbita_8;
    delete planeta_4;
    delete orbita_9;
    delete orbita_10;
    delete ksiezyc_6;
    delete orbita_11;
    delete ksiezyc_7;

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
    orbita_3->getTransform()->rotate(-1,0,0,1);
    {
        planeta_2->getTransform()->rotate(-1,0,1,0);
        orbita_4->getTransform()->rotate(3,0,0,1);
        {
            ksiezyc_2->getTransform()->rotate(5,0,0,1);
        }
        orbita_5->getTransform()->rotate(2,0,0,1);
        {
            ksiezyc_3->getTransform()->rotate(4,0,0,1);
        }
    }
    orbita_6->getTransform()->rotate(0.5,0,0,1);
    {
        //planeta_3->getTransform()->rotate(1,0,0,1);
        orbita_7->getTransform()->rotate(2,0,0,1);
        {
            //ksiezyc_4->getTransform()->rotate(1,0,0,1);
        }
    }
    orbita_8->getTransform()->rotate(0.1,0,0,1);
    {
        planeta_4->getTransform()->rotate(1,0.1,0.2,0.3);
        orbita_9->getTransform()->rotate(2,0,0,1);
        {
            ksiezyc_5->getTransform()->rotate(1,1,0,0);
        }
        orbita_10->getTransform()->rotate(2,0,0,1);
        {
            ksiezyc_6->getTransform()->rotate(1,1,0,0);
        }
        orbita_11->getTransform()->rotate(2,0,0,1);
        {
            ksiezyc_7->getTransform()->rotate(1,1,0,0);
        }
    }

    scene_graph->update();
    scene_graph->render(shader);
}

void UkladPlanet::gui()
{
    ImGui::Begin("GUI");
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
        planeta_2->setDisplayMode(show_grid);
        //planeta_3->setDisplayMode(show_grid);
        planeta_4->setDisplayMode(show_grid);

        ksiezyc_1->setDisplayMode(show_grid);
        ksiezyc_2->setDisplayMode(show_grid);
        ksiezyc_3->setDisplayMode(show_grid);
        //ksiezyc_4->setDisplayMode(show_grid);
        ksiezyc_5->setDisplayMode(show_grid);
        ksiezyc_6->setDisplayMode(show_grid);
        ksiezyc_7->setDisplayMode(show_grid);
    }
    ImGui::Checkbox("X", &obrot_x);
    ImGui::SameLine();
    ImGui::Checkbox("Y", &obrot_y);
    ImGui::SameLine();
    ImGui::Checkbox("Z", &obrot_z);
    ImGui::SliderFloat("Zoom", &zoom, -20, 20);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 0.001*ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();


    camera->setPosition(0,0,zoom);
    scene_graph->getTransform()->setView(camera->getView());
}
