#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

class Texture
{
private:
    unsigned int texture;

    int width;
    int height;
    int nrChannels;

public:
    Texture();
    bool loadFromFile(std::string file);
    void bindTexture();
    void unbindTexture();
};

#endif // __TEXTURE_H__
