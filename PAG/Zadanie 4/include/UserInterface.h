#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Koparka.h"

class UserInterface
{
public:

    bool directional_light_enable;
    float directional_light_direction[3];
    float directional_light_color[3];

    bool point_light_enable;
    bool point_light_spin;
    float point_lightSku;
    float point_lightWli;
    float point_lightWkw;
    float point_light_position[3];
    float point_light_color[3];

    bool spot_light_1_enable;
    float spot_light_1_range;
    float spot_light_1_position[3];
    float spot_light_1_direction[3];
    float spot_light_1_color[3];
    float spot_light_1_radius[2];

    bool spot_light_2_enable;
    float spot_light_2_range;
    float spot_light_2_position[3];
    float spot_light_2_direction[3];
    float spot_light_2_color[3];
    float spot_light_2_radius[2];

    /// koparka
    Koparka* koparka;
    float oska;
    float ramie_1;
    float ramie_2;
    float szufla;
    float kolo;
    float kola;

public:
    UserInterface(GLFWwindow* window);
    ~UserInterface();

    void Display();
};

#endif // __USERINTERFACE_H__
