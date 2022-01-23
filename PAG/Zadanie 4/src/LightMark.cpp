#include "LightMark.h"

LightMark::LightMark()
{

}

LightMark::~LightMark()
{

}

void LightMark::Create(Shader* shader, float size_x, float size_y, float size_z, float offset_x, float offset_y, float offset_z)
{
    this->shader = shader;

    float vertices[] =
    {
        /// x y z - pos --- x y z - normal --- x t - texture coord
        -0.5f*size_x, -0.5f*size_y, -0.5f*size_z,     0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f,

            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,   0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,   0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,   0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,

            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,

            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f
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
    glEnableVertexAttribArray(1);
}

void LightMark::Draw()
{
    shader->use();
    shader->setMat4("model", transform);
    shader->setBool("mark", true);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    shader->setBool("mark", false);
}
