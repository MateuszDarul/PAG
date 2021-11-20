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


    Texture* texture_1;


    Shape* slonce;
///------------------------------------------------------------------
    Shape* orbita_1;
    Shape* planeta_1;
    Shape* orbita_2;
    Shape* ksiezyc_1;
///------------------------------------------------------------------
    Shape* orbita_3;
    Shape* planeta_2;
    Shape* orbita_4;
    Shape* ksiezyc_2;
    Shape* orbita_5;
    Shape* ksiezyc_3;
///------------------------------------------------------------------
    Shape* orbita_6;
    Model* planeta_3;
    Shape* orbita_7;
    Model* ksiezyc_4;
///------------------------------------------------------------------
    Shape* orbita_8;
    Shape* planeta_4;
    Shape* orbita_9;
    Shape* ksiezyc_5;
    Shape* orbita_10;
    Shape* ksiezyc_6;
    Shape* orbita_11;
    Shape* ksiezyc_7;


    int sphere_quality;
    int window_size_x;
    int window_size_y;
    bool show_grid;

    bool obrot_x;
    bool obrot_y;
    bool obrot_z;

    float zoom;

public:
    UkladPlanet(int window_size_x, int window_size_y);
    ~UkladPlanet();

    void loop();
    void gui();
};

#endif // __UKLADPLANET_H__
