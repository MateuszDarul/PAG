// ogolne
#include <iostream>
#include <stdio.h>
#include <vector>

// opengl
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

// imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// moje
#include "ImGUI.h"
#include "Shader.h"


static void glfw_error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        return 1;
    }

    // Ustawiamy GL na wersje 4.5 i GLSL na wersje 450
    const char* glsl_version = "#version 450";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Tworzymy okno z kontekstem graficznym
    GLFWwindow* window = glfwCreateWindow(800, 800, "Piramida", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Nie udalo sie utworzyc okna" << std::endl;
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializacja OpenGL loader'a
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Inicializacja OpenGL nie powiodla sie" << std::endl;
        return 3;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGUI moje_gui;

    //...

    glEnable(GL_DEPTH_TEST);

    ///***

    Shader *shader = nullptr;
    Shader *shader_col = new Shader("res/shaders/vertexShader.vert", "res/shaders/fragmentShader.frag");
    Shader *shader_tex = new Shader("res/shaders/vertexShader_tex.vert", "res/shaders/fragmentShader_tex.frag");

    shader = shader_col;

    ///***

    // Init
    float vertices[] = {
           0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,  0.5f, 1.0f,
          -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,

           0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,  0.5f, 1.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 0.0f,

           0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  0.5f, 1.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 0.0f,

          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  0.5f, 1.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 0.0f
    };

    std::vector<float> ver;
    for (int i = 0; i < 12 * 5; i++)
    {
        ver.push_back(vertices[i]);
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, ver.size()*sizeof(float), &ver[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    ///***

    auto updateSierpinski = [&ver, &vertices](int iter) -> void
    {
        std::vector<float> new_ver;

        ver.clear();

        for (int i = 0; i < 12 * 5; i++)
        {
            ver.push_back(vertices[i]);
        }

        for (int it = 0; it < iter; it++)
        {
            glm::vec3 w[4];
            glm::vec3 n[6];

            for (int i = 0; i < ver.size()/60; i ++)
            {
                w[0] = glm::vec3(ver[i * 60 + 0], ver[i * 60 + 1], ver[i * 60 + 2]);
                w[1] = glm::vec3(ver[i * 60 + 5], ver[i * 60 + 6], ver[i * 60 + 7]);
                w[2] = glm::vec3(ver[i * 60 + 10], ver[i * 60 + 11], ver[i * 60 + 12]);

                for (int j = 15; j < 60; j += 5)
                {
                    w[3] = glm::vec3(ver[i * 60 + j + 0], ver[i * 60 + j + 1], ver[i * 60 + j + 2]);

                    if (w[3] != w[0] && w[3] != w[1] && w[3] != w[2])
                        break;
                }

                n[0] = glm::vec3((w[0].x + w[1].x) / 2, (w[0].y + w[1].y) / 2, (w[0].z + w[1].z) / 2);
                n[1] = glm::vec3((w[0].x + w[2].x) / 2, (w[0].y + w[2].y) / 2, (w[0].z + w[2].z) / 2);
                n[2] = glm::vec3((w[0].x + w[3].x) / 2, (w[0].y + w[3].y) / 2, (w[0].z + w[3].z) / 2);
                n[3] = glm::vec3((w[1].x + w[2].x) / 2, (w[1].y + w[2].y) / 2, (w[1].z + w[2].z) / 2);
                n[4] = glm::vec3((w[1].x + w[3].x) / 2, (w[1].y + w[3].y) / 2, (w[1].z + w[3].z) / 2);
                n[5] = glm::vec3((w[2].x + w[3].x) / 2, (w[2].y + w[3].y) / 2, (w[2].z + w[3].z) / 2);

                // 1
                new_ver.insert(new_ver.end(), { w[0].x, w[0].y, w[0].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[0].x, n[0].y, n[0].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[1].x, n[1].y, n[1].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[0].x, w[0].y, w[0].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[1].x, n[1].y, n[1].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[2].x, n[2].y, n[2].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[0].x, w[0].y, w[0].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[0].x, n[0].y, n[0].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[2].x, n[2].y, n[2].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { n[0].x, n[0].y, n[0].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[1].x, n[1].y, n[1].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[2].x, n[2].y, n[2].z, 1.f, 0.f });

                // 2
                new_ver.insert(new_ver.end(), { w[1].x, w[1].y, w[1].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[0].x, n[0].y, n[0].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[3].x, n[3].y, n[3].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { n[0].x, n[0].y, n[0].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[3].x, n[3].y, n[3].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[4].x, n[4].y, n[4].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[1].x, w[1].y, w[1].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[0].x, n[0].y, n[0].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[4].x, n[4].y, n[4].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[1].x, w[1].y, w[1].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[3].x, n[3].y, n[3].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[4].x, n[4].y, n[4].z, 1.f, 0.f });

                // 3
                new_ver.insert(new_ver.end(), { w[2].x, w[2].y, w[2].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[1].x, n[1].y, n[1].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[3].x, n[3].y, n[3].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[2].x, w[2].y, w[2].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[1].x, n[1].y, n[1].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[5].x, n[5].y, n[5].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { n[1].x, n[1].y, n[1].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[3].x, n[3].y, n[3].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[5].x, n[5].y, n[5].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[2].x, w[2].y, w[2].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[3].x, n[3].y, n[3].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[5].x, n[5].y, n[5].z, 1.f, 0.f });

                // 4
                new_ver.insert(new_ver.end(), { n[2].x, n[2].y, n[2].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[4].x, n[4].y, n[4].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[5].x, n[5].y, n[5].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[3].x, w[3].y, w[3].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[2].x, n[2].y, n[2].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[5].x, n[5].y, n[5].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[3].x, w[3].y, w[3].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[2].x, n[2].y, n[2].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[4].x, n[4].y, n[4].z, 1.f, 0.f });

                new_ver.insert(new_ver.end(), { w[3].x, w[3].y, w[3].z, 0.f, 0.f });
                new_ver.insert(new_ver.end(), { n[4].x, n[4].y, n[4].z, 0.5, 1.f });
                new_ver.insert(new_ver.end(), { n[5].x, n[5].y, n[5].z, 1.f, 0.f });
            }
        
            ver.clear();
            for (int i = 0; i < new_ver.size(); i++)
            {
                ver.push_back(new_ver[i]);
            }
            new_ver.clear();
        }

        glBufferData(GL_ARRAY_BUFFER, ver.size() * sizeof(float), &ver[0], GL_STATIC_DRAW);
    };

    ///***

    // load and create a texture 
    stbi_set_flip_vertically_on_load(true);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char* data = stbi_load("res/textures/texturka.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ///***

   // glm::mat4 transformacje = glm::mat4(1.0f);
   // transformacje = glm::rotate(transformacje, glm::radians(180.f), glm::vec3(0.0f, 0.0f, 1.0f));
   // transformacje = glm::scale(transformacje, glm::vec3(0.5, 0.5, 0.5));

    ///***

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    //...

    while (!glfwWindowShouldClose(window))
    {
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians((float)moje_gui.obrot_fraktala[0]), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians((float)moje_gui.obrot_fraktala[1]), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians((float)moje_gui.obrot_fraktala[2]), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, moje_gui.zoom));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);

        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);

        processInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        moje_gui.Draw();
        {
            if (moje_gui.pokaz_teksture)
                shader = shader_tex;
            else
                shader = shader_col;

            if (moje_gui.poziom_rekurencji != moje_gui.tmp_poziom_rekurencji)
            {
                updateSierpinski(moje_gui.poziom_rekurencji);
                moje_gui.tmp_poziom_rekurencji = moje_gui.poziom_rekurencji;
            }
        }
        ImGui::Render();

        glClearColor(moje_gui.kolor_tla.x, moje_gui.kolor_tla.y, moje_gui.kolor_tla.z, moje_gui.kolor_tla.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        //shader->setMat4("transform", transformacje);
        shader->set4Float("myColor", moje_gui.kolor_fraktala.x, moje_gui.kolor_fraktala.y, moje_gui.kolor_fraktala.z, 1);

        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, ver.size()/5);


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete shader_col;
    delete shader_tex;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}