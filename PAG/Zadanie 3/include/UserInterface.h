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

class UserInterface
{
private:

public:
    UserInterface(GLFWwindow* window);
    ~UserInterface();

    void Display();
};

#endif // __USERINTERFACE_H__
