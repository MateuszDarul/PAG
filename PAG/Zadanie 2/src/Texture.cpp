#include "Texture.h"

Texture::Texture()
{

}

bool Texture::loadFromFile(std::string file)
{
    std::string ext;
    int letter_of_extension = 0;
    for(int i=file.length()-1; i>0; i--)
    {
        letter_of_extension++;
        if(file[i] == '.')
            break;
    }

    for(int i=file.length()-letter_of_extension; i<file.length(); i++)
        ext.push_back(file[i]);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
    if(data)
    {
        if(ext == ".jpg")
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if(ext == ".png")
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cerr << "Unknown file extension, please use (jpg or png)" << std::endl;
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
        return false;
    }
    stbi_image_free(data);
    return true;
}

void Texture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
