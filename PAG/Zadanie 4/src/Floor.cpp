#include "Floor.h"

Floor::Floor()
{
    //ctor
}

Floor::~Floor()
{
    //dtor
}

void Floor::Create(Shader* shader, float size_x, float size_y, float size_z, float offset_x, float offset_y, float offset_z)
{
    this->shader = shader;

    float vertices[] =
    {
        /// x y z - pos --- x y z - normal --- x t - texture coord
        1.0f*size_x, size_y,  1.0f*size_z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f*size_x, size_y,  1.0f*size_z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f*size_x, size_y, -1.0f*size_z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f*size_x, size_y,  1.0f*size_z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f*size_x, size_y, -1.0f*size_z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f*size_x, size_y, -1.0f*size_z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
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




    glGenTextures(1, &TEX);
    glBindTexture(GL_TEXTURE_2D, TEX);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    const char* file_name = "resources/textures/Ground.jpg";
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

void Floor::Draw()
{
    shader->use();
    shader->setMat4("model", transform);

    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, TEX);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
