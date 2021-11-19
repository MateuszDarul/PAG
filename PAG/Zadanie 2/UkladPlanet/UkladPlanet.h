#ifndef __UKLADPLANET_H__
#define __UKLADPLANET_H__

#include <iostream>


#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include "Shader.h"
#include "SceneGraph.h"
#include "Camera.h"
#include "Shape.h"
#include "Model.h"

class UkladPlanet
{
private:
    Shader* shader;
    SceneGraph* scene_graph;
    Camera* camera;


    Shape* slonce;

    Shape* orbita_1;
    Shape* planeta_1;
    Shape* orbita_2;
    Shape* ksiezyc_1;


    int sphere_quality;
    int window_size_x;
    int window_size_y;
    bool show_grid;

    bool obrot_x;
    bool obrot_y;
    bool obrot_z;

public:
    UkladPlanet(int window_size_x, int window_size_y);
    ~UkladPlanet();

    void loop();
    void gui();
};

#endif // __UKLADPLANET_H__
