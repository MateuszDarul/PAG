#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <vector>

using namespace std;

#define MAX_BONE_INFLUENCE 4

struct AssimpVertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    glm::vec3 Tangent;
    glm::vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct AssimpTexture
{
    unsigned int id;
    string type;
    string path;
};

class Mesh
{
private:
    unsigned int VAO, VBO, EBO;

    vector<AssimpVertex> vertices;
    vector<unsigned int> indices;
    vector<AssimpTexture> textures;

private:
    void generate();

public:
    Mesh(vector<AssimpVertex> vertices, vector<unsigned int> indices, vector<AssimpTexture> textures);
    void draw(Shader &shader);
};
#endif
