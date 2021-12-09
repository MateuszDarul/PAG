#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "UserInterface.h"
#include "Shader.h"
#include "SceneGraphNode.h"
#include "Transform.h"
#include "Camera.h"

#include "RenderObject.h"
#include "Floor.h"

void processInput(GLFWwindow *window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

/// FPS limit
double frame_time = 1.0/60.0;

/// Window size
unsigned int screen_width = 800;
unsigned int screen_height = 600;

/// Camera
Camera camera(glm::vec3(0.0f, 10.0f, 128.0f));
float lastX = (float)screen_width / 2.0;
float lastY = (float)screen_height / 2.0;
bool firstMouse = true;

/// Menu enable
bool enable_menu = false;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(false);

    UserInterface* user_interface = new UserInterface(window);

    Shader shader("resources/shaders/vertexShader.vert", "resources/shaders/fragmentShader.frag");
    std::shared_ptr<SceneGraphNode> scene = std::make_shared<SceneGraphNode>();

    std::shared_ptr<RenderObject> floor = std::make_shared<Floor>();
    floor->Create(128,0,128);
    std::shared_ptr<SceneGraphNode> floor_node = std::make_shared<SceneGraphNode>(floor);
    scene->AddChild(floor_node);

    std::shared_ptr<RenderObject> cube = std::make_shared<Cube>();
    cube->Create(20,20,20);
    std::shared_ptr<SceneGraphNode> cube_node = std::make_shared<SceneGraphNode>(cube);
    cube_node->GetTransform().position += glm::vec3(20, 10, 0);
    floor_node->AddChild(cube_node);

    double last_time = glfwGetTime();
    double unprecessed_time = 0.0;
    double current_time = 0.0;
    double passed_time = 0.0;
    bool should_render = false;

    Transform camera_transformations;
    Transform old_camera_transformations;

    while(!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        passed_time = current_time - last_time;
        last_time = current_time;
        unprecessed_time += passed_time;

        /// input
        processInput(window);


        /// update
        while(unprecessed_time >= frame_time)
        {
            should_render = true;
            unprecessed_time -= frame_time;


            cube_node->GetTransform().position += glm::vec3(-0.1, 0, 0);

            /// camera
            camera_transformations.world_matrix =
                glm::perspective(glm::radians(45.0f), (float)screen_width/(float)screen_height, 0.1f, 1000.0f)
                *
                camera.GetViewMatrix();
            bool camera_change = old_camera_transformations.world_matrix != camera_transformations.world_matrix;
            scene->Update(camera_transformations, camera_change);
            old_camera_transformations = camera_transformations;
        }

        /// render
        if(should_render)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



            scene->Render(shader, true);



            user_interface->Display();

            glfwSwapBuffers(window);
            should_render = false;
        }

        glfwPollEvents();
    }

    delete user_interface;

    glfwTerminate();

    return 0;
}

bool isPressed = false;
bool old_isPressed = false;
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, frame_time);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, frame_time);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, frame_time);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, frame_time);
    }


    if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        isPressed = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
    {
        isPressed = false;
    }
    if(isPressed != old_isPressed)
    {
        old_isPressed = !old_isPressed;

        if(isPressed)
        {
            if(enable_menu)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            enable_menu = !enable_menu;
        }
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    screen_width = width;
    screen_height = height;
    glViewport(0, 0, screen_width, screen_height);
}
