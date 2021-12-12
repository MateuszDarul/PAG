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
unsigned int screen_width = 1600;
unsigned int screen_height = 800;

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

    Shader shader_default("resources/shaders/vertexShader.vert", "resources/shaders/fragmentShader.frag");


    glm::vec3 tr[ilosc_instancji*ilosc_instancji];
    int x=0, y=0;
    for (int i = 0; i < ilosc_instancji*ilosc_instancji; i++)
    {
        tr[i] = glm::vec3(x*5, 0, y*5);

        x++;
        if(x % ilosc_instancji == 0)
        {
            x=0;
            y++;
        }
    }

    std::shared_ptr<SceneGraphNode> scene = std::make_shared<SceneGraphNode>();

    std::shared_ptr<RenderObject> floor = std::make_shared<Floor>();
    floor->Create(&shader_default, 512,0,512);
    std::shared_ptr<SceneGraphNode> floor_node = std::make_shared<SceneGraphNode>(floor);
    scene->AddChild(floor_node);

    std::shared_ptr<RenderObject> cube = std::make_shared<Cube>(tr);
    cube->Create(&shader_default, 1,1,1);
    std::shared_ptr<SceneGraphNode> domki = std::make_shared<SceneGraphNode>(cube);
    domki->GetTransform().position += glm::vec3(-510, 0.5, -510);
    floor_node->AddChild(domki);

    std::shared_ptr<RenderObject> pyramid = std::make_shared<Pyramid>(tr);
    pyramid->Create(&shader_default, 1.5,1,1.5);
    std::shared_ptr<SceneGraphNode> dachy = std::make_shared<SceneGraphNode>(pyramid);
    dachy->GetTransform().position += glm::vec3(0, 1, 0);
    domki->AddChild(dachy);


    std::shared_ptr<RenderObject> light_box_1 = std::make_shared<LightMark>();
    light_box_1->Create(&shader_default, 1,1,1);
    std::shared_ptr<SceneGraphNode> light_box_1_node = std::make_shared<SceneGraphNode>(light_box_1);
    floor_node->AddChild(light_box_1_node);

    std::shared_ptr<RenderObject> light_box_2 = std::make_shared<LightMark>();
    light_box_2->Create(&shader_default, 1,1,1);
    std::shared_ptr<SceneGraphNode> light_box_2_node = std::make_shared<SceneGraphNode>(light_box_2);
    floor_node->AddChild(light_box_2_node);

    std::shared_ptr<RenderObject> light_box_3 = std::make_shared<LightMark>();
    light_box_3->Create(&shader_default, 1,1,1);
    std::shared_ptr<SceneGraphNode> light_box_3_node = std::make_shared<SceneGraphNode>(light_box_3);
    floor_node->AddChild(light_box_3_node);

    double last_time = glfwGetTime();
    double unprecessed_time = 0.0;
    double current_time = 0.0;
    double passed_time = 0.0;
    bool should_render = false;

    glm::mat4 projection;
    glm::mat4 view;

    float kat = 0, promien=510;

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
            if(user_interface->point_light_spin)
            {
                kat += 0.001;
                user_interface->point_light_position[0] = cos( kat ) * promien;
                user_interface->point_light_position[1] = 5.f;
                user_interface->point_light_position[2] = sin( kat ) * promien;
            }
            light_box_1_node->GetTransform().position = glm::vec3(user_interface->point_light_position[0],
                                                                  user_interface->point_light_position[1],
                                                                  user_interface->point_light_position[2]);


            light_box_2_node->GetTransform().position = glm::vec3(user_interface->spot_light_1_position[0],
                                                                  user_interface->spot_light_1_position[1],
                                                                  user_interface->spot_light_1_position[2]);

            light_box_3_node->GetTransform().position = glm::vec3(user_interface->spot_light_2_position[0],
                                                                  user_interface->spot_light_2_position[1],
                                                                  user_interface->spot_light_2_position[2]);

            should_render = true;
            unprecessed_time -= frame_time;

            /// camera
            projection = glm::perspective(glm::radians(45.0f), (float)screen_width/(float)screen_height, 0.1f, 1000.0f);
            view = camera.GetViewMatrix();

            scene->Update(Transform(), false);
        }

        /// render
        if(should_render)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader_default.use();
            shader_default.setMat4("projection", projection);
            shader_default.setMat4("view", view);

            shader_default.setVec3("viewPos", camera.GetPosition());

            shader_default.setBool("point_light_enable", user_interface->point_light_enable);
            shader_default.setFloat("point_lightSku", user_interface->point_lightSku);
            shader_default.setFloat("point_lightWli", user_interface->point_lightWli);
            shader_default.setFloat("point_lightWkw", user_interface->point_lightWkw);
            shader_default.setVec3("point_lightPos",
            glm::vec3(user_interface->point_light_position[0],
                      user_interface->point_light_position[1],
                      user_interface->point_light_position[2]));
            shader_default.setVec3("point_lightCol",
            glm::vec3(user_interface->point_light_color[0],
                      user_interface->point_light_color[1],
                      user_interface->point_light_color[2]));

            shader_default.setBool("directional_light_enable", user_interface->directional_light_enable);
            shader_default.setVec3("direction_lightDir",
            glm::vec3(user_interface->directional_light_direction[0],
                      user_interface->directional_light_direction[1],
                      user_interface->directional_light_direction[2]));
            shader_default.setVec3("direction_lightCol",
            glm::vec3(user_interface->directional_light_color[0],
                      user_interface->directional_light_color[1],
                      user_interface->directional_light_color[2]));


            shader_default.setBool("spot_1_light_enable", user_interface->spot_light_1_enable);
            shader_default.setVec3("light_1.position",
            glm::vec3(user_interface->spot_light_1_position[0],
                      user_interface->spot_light_1_position[1],
                      user_interface->spot_light_1_position[2]));
            shader_default.setVec3("light_1.direction",
            glm::vec3(user_interface->spot_light_1_direction[0],
                      user_interface->spot_light_1_direction[1],
                      user_interface->spot_light_1_direction[2]));
            shader_default.setFloat("light_1.cutOff", glm::cos(glm::radians(12.5f)));
            shader_default.setFloat("light_1.outerCutOff", glm::cos(glm::radians(17.5f)));
            shader_default.setVec3("light_1.specular", 1.f, 1.f, 1.f);
            shader_default.setFloat("light_1.constant", 1.0f);
            shader_default.setFloat("light_1.linear", user_interface->spot_light_1_range);
            shader_default.setFloat("light_1.quadratic", 0.00f);
            shader_default.setFloat("material_1.shininess", 32.0f);
            shader_default.setVec3("light_1.ambient", 0.f, 0.f, 0.f);
            shader_default.setVec3("light_1.diffuse",
            glm::vec3(user_interface->spot_light_1_color[0],
                      user_interface->spot_light_1_color[1],
                      user_interface->spot_light_1_color[2]));

            shader_default.setBool("spot_2_light_enable", user_interface->spot_light_2_enable);
            shader_default.setVec3("light_2.position",
            glm::vec3(user_interface->spot_light_2_position[0],
                      user_interface->spot_light_2_position[1],
                      user_interface->spot_light_2_position[2]));
            shader_default.setVec3("light_2.direction",
            glm::vec3(user_interface->spot_light_2_direction[0],
                      user_interface->spot_light_2_direction[1],
                      user_interface->spot_light_2_direction[2]));
            shader_default.setFloat("light_2.cutOff", glm::cos(glm::radians(12.5f)));
            shader_default.setFloat("light_2.outerCutOff", glm::cos(glm::radians(17.5f)));
            shader_default.setVec3("light_2.specular", 1.f, 1.f, 1.f);
            shader_default.setFloat("light_2.constant", 1.0f);
            shader_default.setFloat("light_2.linear", user_interface->spot_light_2_range);
            shader_default.setFloat("light_2.quadratic", 0.00f);
            shader_default.setFloat("material_2.shininess", 32.0f);
            shader_default.setVec3("light_2.ambient", 0.f, 0.f, 0.f);
            shader_default.setVec3("light_2.diffuse",
            glm::vec3(user_interface->spot_light_2_color[0],
                      user_interface->spot_light_2_color[1],
                      user_interface->spot_light_2_color[2]));

            scene->Render(true);

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
            enable_menu = !enable_menu;
            if(enable_menu)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if(enable_menu)return;

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
