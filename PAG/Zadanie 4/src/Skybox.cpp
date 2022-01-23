#include "Skybox.h"

Skybox::Skybox()
{

}

void Skybox::Create(Shader* shader, float size_x, float size_y, float size_z, float offset_x, float offset_y, float offset_z)
{
    this->shader = shader;

    float vertices[] =
    {
        -0.5f*size_x, -0.5f*size_y, -0.5f*size_z,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z,

            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z,

            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z,

            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,

            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z,
            0.5f*size_x, -0.5f*size_y, -0.5f*size_z,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,
            0.5f*size_x, -0.5f*size_y,  0.5f*size_z,
            -0.5f*size_x, -0.5f*size_y,  0.5f*size_z,
            -0.5f*size_x, -0.5f*size_y, -0.5f*size_z,

            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z,
            0.5f*size_x,  0.5f*size_y, -0.5f*size_z,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,
            0.5f*size_x,  0.5f*size_y,  0.5f*size_z,
            -0.5f*size_x,  0.5f*size_y,  0.5f*size_z,
            -0.5f*size_x,  0.5f*size_y, -0.5f*size_z
        };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    std::vector<std::string> faces
    {
        ("resources/textures/skybox/right.jpg"),
        ("resources/textures/skybox/left.jpg"),
        ("resources/textures/skybox/top.jpg"),
        ("resources/textures/skybox/bottom.jpg"),
        ("resources/textures/skybox/front.jpg"),
        ("resources/textures/skybox/back.jpg")
    };

    glGenTextures(1, &cubemap_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);

    int width, height, nrChannels;
    for(unsigned int i=0; i<faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if(data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    shader->use();
    shader->setInt("skybox", 0);
}

void Skybox::Draw()
{
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

unsigned int* Skybox::GetSkyboxTexture()
{
    return &cubemap_texture;
}
