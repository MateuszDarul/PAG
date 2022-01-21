#include "Glass.h"

Glass::Glass(unsigned int* cubemap_texture)
{
    this->cubemap_texture = cubemap_texture;
}

void Glass::Create(Shader* shader, float size_x, float size_y, float size_z)
{
    this->shader = shader;

    float vectices[] = {
        -0.5f*size_x, -0.5f*size_y, -0.5f*size_z,     0.0f,  0.0f, -1.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  0.0f,  0.0f, -1.0f,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,  0.0f,  0.0f, -1.0f,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,  0.0f,  0.0f, -1.0f,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z, 0.0f,  0.0f, -1.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0.0f,  0.0f, -1.0f,

            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0.0f,  0.0f, 1.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,   0.0f,  0.0f, 1.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,   0.0f,  0.0f, 1.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,   0.0f,  0.0f, 1.0f,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  0.0f,  0.0f, 1.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0.0f,  0.0f, 1.0f,

            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z, -1.0f,  0.0f,  0.0f,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z, -1.0f,  0.0f,  0.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, -1.0f,  0.0f,  0.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, -1.0f,  0.0f,  0.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z, -1.0f,  0.0f,  0.0f,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z, -1.0f,  0.0f,  0.0f,

            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  1.0f,  0.0f,  0.0f,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,  1.0f,  0.0f,  0.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  1.0f,  0.0f,  0.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  1.0f,  0.0f,  0.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  1.0f,  0.0f,  0.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  1.0f,  0.0f,  0.0f,

            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0.0f, -1.0f,  0.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  0.0f, -1.0f,  0.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0.0f, -1.0f,  0.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0.0f, -1.0f,  0.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z, 0.0f, -1.0f,  0.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0.0f, -1.0f,  0.0f,

            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z, 0.0f,  1.0f,  0.0f,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,  0.0f,  1.0f,  0.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  0.0f,  1.0f,  0.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  0.0f,  1.0f,  0.0f,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z, 0.0f,  1.0f,  0.0f,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z, 0.0f,  1.0f,  0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vectices), &vectices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader->use();
    shader->setInt("skybox", 0);
}

void Glass::Draw()
{
    shader->use();
    shader->setMat4("model", transform);

    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *cubemap_texture);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
