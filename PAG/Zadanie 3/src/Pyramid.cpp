#include "Pyramid.h"

Pyramid::Pyramid(glm::vec3 *transformations)
{
    this->transformations = transformations;
}

Pyramid::~Pyramid()
{
    //dtor
}

void Pyramid::Create(Shader* shader, float size_x, float size_y, float size_z)
{
    this->shader = shader;

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*ilosc_instancji*ilosc_instancji, &transformations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float vertices[] =
    {
        -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0, -1, 0, 1.0f, 0.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  0, -1, 0, 1.0f, 1.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0, -1, 0, 0.0f, 1.0f,

            0.5f*size_x, -0.5f*size_y,  0.5f*size_z, 0, -1, 0, 0.0f, 1.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z, 0, -1, 0, 0.0f, 0.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0, -1, 0, 1.0f, 0.0f,

            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0, 1, -1, 0.0f, 0.0f,
            0, 0.5*size_y, 0,0, 1, -1, 0.5f, 1.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0, 1, -1, 1.0f, 0.0f,

            0.5f*size_x, -0.5f*size_y,  0.5f*size_z, 0, 1, 1, 0.0f, 0.0f,
            0, 0.5*size_y, 0, 0, 1, 1, 0.5f, 1.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z, 0, 1, 1, 1.0f, 0.0f,

            0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 1, 1, 0,  0.0f, 0.0f,
            0, 0.5*size_y, 0, 1, 1, 0, 0.5f, 1.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z, 1, 1, 0, 1.0f, 0.0f,

            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, -1, 1, 0, 0.0f, 0.0f,
            0, 0.5*size_y, 0, -1, 1, 0, 0.5f, 1.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z, -1, 1, 0, 1.0f, 0.0f
        };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1);


    glGenTextures(1, &TEX);
    glBindTexture(GL_TEXTURE_2D, TEX);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    const char* file_name = "resources/textures/Roof.jpg";
    data = stbi_load(file_name, &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Pyramid::Draw()
{
    shader->use();
    shader->setMat4("model", transform);

    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, TEX);

    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 18, ilosc_instancji*ilosc_instancji);
}
