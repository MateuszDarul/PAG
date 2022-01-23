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
#include "Koparka.h"

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
bool driver_mode = false;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Koparka", NULL, NULL);
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

    Shader shader_default("resources/shaders/main.vert", "resources/shaders/main.frag");
    Shader shader_instance("resources/shaders/instance.vert", "resources/shaders/instance.frag");
    Shader shader_skybox("resources/shaders/skybox.vert", "resources/shaders/skybox.frag");
    Shader shader_reflect("resources/shaders/reflect.vert", "resources/shaders/reflect.frag");
    Shader shader_refract("resources/shaders/refract.vert", "resources/shaders/refract.frag");

    glm::mat4* model_matrices_dom;
    glm::mat4* model_matrices_dach;
    model_matrices_dom = new glm::mat4[ilosc_instancji*ilosc_instancji];
    model_matrices_dach = new glm::mat4[ilosc_instancji*ilosc_instancji];
    int x=0, y=0;
    for (int i = 0; i < ilosc_instancji*ilosc_instancji; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);

        model_matrices_dom[i] = glm::translate(model, glm::vec3(x*5-497.5, 0.5, y*5-497.5));
        model_matrices_dach[i] = glm::translate(model, glm::vec3(x*5-497.5, 1.5, y*5-497.5));

        x++;
        if(x % ilosc_instancji == 0)
        {
            x=0;
            y++;
        }
    }

    Skybox skybox;
    skybox.Create(&shader_skybox, 2, 2, 2);

    std::shared_ptr<SceneGraphNode> scene = std::make_shared<SceneGraphNode>();

    std::shared_ptr<RenderObject> floor = std::make_shared<Floor>();
    floor->Create(&shader_default, 500,0,500);
    std::shared_ptr<SceneGraphNode> floor_node = std::make_shared<SceneGraphNode>(floor);
    scene->AddChild(floor_node);

    std::shared_ptr<RenderObject> cube = std::make_shared<Cube>(model_matrices_dom);
    cube->Create(&shader_instance, 1,1,1);
    std::shared_ptr<SceneGraphNode> domki = std::make_shared<SceneGraphNode>(cube);
    floor_node->AddChild(domki);

    std::shared_ptr<RenderObject> pyramid = std::make_shared<Pyramid>(model_matrices_dach);
    pyramid->Create(&shader_instance, 1.5,1,1.5);
    std::shared_ptr<SceneGraphNode> dachy = std::make_shared<SceneGraphNode>(pyramid);
    domki->AddChild(dachy);


    ///---
    Shader* shader_list[3];
    shader_list[0] = &shader_default;
    shader_list[1] = &shader_reflect;
    shader_list[2] = &shader_refract;
    Koparka koparka(floor_node, shader_list, &skybox);
    user_interface->koparka = &koparka;
    ///---


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
    glm::vec3 move_vector = glm::vec3(0,0,0);

    while(!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        passed_time = current_time - last_time;
        last_time = current_time;
        unprecessed_time += passed_time;

        /// input
        processInput(window);
        {
            if(driver_mode)
            {
                if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                {
                    camera.ProcessKeyboard(FORWARD, frame_time);
                    user_interface->kolo -= 0.002;
                    koparka.Kolo(0, user_interface->kolo);
                    koparka.Kolo(1, user_interface->kolo);
                    koparka.Kolo(2, user_interface->kolo);
                    koparka.Kolo(3, user_interface->kolo);
                    koparka.Move(glm::vec3(0.0002 * camera.Front.x, 0, 0.0002 * camera.Front.z));
                }
                if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                {
                    camera.ProcessKeyboard(BACKWARD, frame_time);
                    user_interface->kolo += 0.002;
                    koparka.Kolo(0, user_interface->kolo);
                    koparka.Kolo(1, user_interface->kolo);
                    koparka.Kolo(2, user_interface->kolo);
                    koparka.Kolo(3, user_interface->kolo);
                    koparka.Move(glm::vec3(-0.0002 * camera.Front.x, 0, -0.0002 * camera.Front.z));
                }
                if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                {
                    camera.ProcessKeyboard(LEFT, frame_time);
                    if(user_interface->kola < 45)
                    {
                        user_interface->kola += 0.002;
                        koparka.Kola(user_interface->kola);
                    }
                    koparka.GetNode(0)->GetTransform().rotation.y += 0.0005;
                }
                if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                {
                    camera.ProcessKeyboard(RIGHT, frame_time);
                    if(user_interface->kola > -45)
                    {
                        user_interface->kola -= 0.002;
                        koparka.Kola(user_interface->kola);
                    }
                    koparka.GetNode(0)->GetTransform().rotation.y -= 0.0005;
                }

                camera.Position = koparka.GetNode(0)->GetTransform().position;
                camera.Position -= glm::vec3(camera.Front.x*100, camera.Front.y*100, camera.Front.z*100);
            }
            else
            {
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
            }
        }


        /// update
        while(unprecessed_time >= frame_time)
        {
            if(user_interface->point_light_spin)
            {
                kat += 0.001;
                user_interface->point_light_position[0] = cos( kat ) * promien;
                user_interface->point_light_position[1] = 50.f;
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

            Shader* shaders[2];
            shaders[0] = &shader_default;
            shaders[1] = &shader_instance;
            for(int i=0; i<2; i++)
            {
                Shader* shader = shaders[i];
                shader->use();
                shader->setMat4("projection", projection);
                shader->setMat4("view", view);
                shader->setVec3("viewPos", camera.GetPosition());

                ///---Point---///

                shader->setBool("point_light_enable", user_interface->point_light_enable);
                shader->setVec3("point_light.position",
                                glm::vec3(user_interface->point_light_position[0],
                                          user_interface->point_light_position[1],
                                          user_interface->point_light_position[2]));
                shader->setVec3("point_light.ambient", 0, 0, 0);
                shader->setVec3("point_light.diffuse",
                                glm::vec3(user_interface->point_light_color[0],
                                          user_interface->point_light_color[1],
                                          user_interface->point_light_color[2]));
                shader->setVec3("point_light.specular", 1.0f, 1.0f, 1.0f);
                shader->setFloat("point_light.constant", 1.0f);
                shader->setFloat("point_light.linear", user_interface->point_lightWli);
                shader->setFloat("point_light.quadratic", user_interface->point_lightWkw);
                shader->setFloat("point_material.shininess", user_interface->point_lightSku);

                ///------///
                ///---Directional---///

                shader->setBool("directional_light_enable", user_interface->directional_light_enable);
                shader->setVec3("directional_light.direction",
                                glm::vec3(user_interface->directional_light_direction[0],
                                          user_interface->directional_light_direction[1],
                                          user_interface->directional_light_direction[2]));
                shader->setVec3("directional_light.ambient", 0.2f, 0.2f, 0.2f);
                shader->setVec3("directional_light.diffuse",
                                glm::vec3(user_interface->directional_light_color[0],
                                          user_interface->directional_light_color[1],
                                          user_interface->directional_light_color[2]));
                shader->setVec3("directional_light.specular", 1.0f, 1.0f, 1.0f);
                shader->setFloat("directional_material.shininess", 32.0f);

                ///------///
                ///---Spot 1---///

                shader->setBool("spot_1_light_enable", user_interface->spot_light_1_enable);
                shader->setVec3("light_1.position",
                                glm::vec3(user_interface->spot_light_1_position[0],
                                          user_interface->spot_light_1_position[1],
                                          user_interface->spot_light_1_position[2]));
                shader->setVec3("light_1.direction",
                                glm::vec3(user_interface->spot_light_1_direction[0],
                                          user_interface->spot_light_1_direction[1],
                                          user_interface->spot_light_1_direction[2]));
                shader->setFloat("light_1.cutOff", glm::cos(glm::radians(user_interface->spot_light_1_radius[0])));
                shader->setFloat("light_1.outerCutOff", glm::cos(glm::radians(user_interface->spot_light_1_radius[0]+user_interface->spot_light_1_radius[1])));
                shader->setVec3("light_1.specular", 1.f, 1.f, 1.f);
                shader->setFloat("light_1.constant", 1.0f);
                shader->setFloat("light_1.linear", user_interface->spot_light_1_range);
                shader->setFloat("light_1.quadratic", 0.00f);
                shader->setFloat("material_1.shininess", 32.0f);
                shader->setVec3("light_1.ambient", 0.f, 0.f, 0.f);
                shader->setVec3("light_1.diffuse",
                                glm::vec3(user_interface->spot_light_1_color[0],
                                          user_interface->spot_light_1_color[1],
                                          user_interface->spot_light_1_color[2]));

                ///------///
                ///---Spot 2---///

                shader->setBool("spot_2_light_enable", user_interface->spot_light_2_enable);
                shader->setVec3("light_2.position",
                                glm::vec3(user_interface->spot_light_2_position[0],
                                          user_interface->spot_light_2_position[1],
                                          user_interface->spot_light_2_position[2]));
                shader->setVec3("light_2.direction",
                                glm::vec3(user_interface->spot_light_2_direction[0],
                                          user_interface->spot_light_2_direction[1],
                                          user_interface->spot_light_2_direction[2]));
                shader->setFloat("light_2.cutOff", glm::cos(glm::radians(user_interface->spot_light_2_radius[0])));
                shader->setFloat("light_2.outerCutOff", glm::cos(glm::radians(user_interface->spot_light_2_radius[0]+user_interface->spot_light_2_radius[1])));
                shader->setVec3("light_2.specular", 1.f, 1.f, 1.f);
                shader->setFloat("light_2.constant", 1.0f);
                shader->setFloat("light_2.linear", user_interface->spot_light_2_range);
                shader->setFloat("light_2.quadratic", 0.00f);
                shader->setFloat("material_2.shininess", 32.0f);
                shader->setVec3("light_2.ambient", 0.f, 0.f, 0.f);
                shader->setVec3("light_2.diffuse",
                                glm::vec3(user_interface->spot_light_2_color[0],
                                          user_interface->spot_light_2_color[1],
                                          user_interface->spot_light_2_color[2]));

                ///------///
            }

            shader_reflect.use();
            shader_reflect.setMat4("view", view);
            shader_reflect.setMat4("projection", projection);
            shader_reflect.setVec3("camera_pos", camera.GetPosition());

            shader_refract.use();
            shader_refract.setMat4("view", view);
            shader_refract.setMat4("projection", projection);
            shader_refract.setVec3("camera_pos", camera.GetPosition());

            scene->Render(true);

            glDepthFunc(GL_LEQUAL);
            shader_skybox.use();
            view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
            shader_skybox.setMat4("view", view);
            shader_skybox.setMat4("projection", projection);
            skybox.Draw();
            glDepthFunc(GL_LESS);

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

bool isPressed_TAB = false;
bool old_isPressed_TAB = false;
bool isPressed_SHIFT = false;
bool old_isPressed_SHIFT = false;
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }


    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        isPressed_SHIFT = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        isPressed_SHIFT = false;
    }
    if(isPressed_SHIFT != old_isPressed_SHIFT)
    {
        old_isPressed_SHIFT = !old_isPressed_SHIFT;

        if(isPressed_SHIFT)
        {
            driver_mode = !driver_mode;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        isPressed_TAB = true;
    }
    else if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
    {
        isPressed_TAB = false;
    }
    if(isPressed_TAB != old_isPressed_TAB)
    {
        old_isPressed_TAB = !old_isPressed_TAB;

        if(isPressed_TAB)
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
