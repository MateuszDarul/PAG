#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Drawable.h"

using namespace std;

class Model : public Drawable
{
private:
    Shader *shader;
    vector<AssimpTexture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    vector<AssimpTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

public:
    Model(string const &path, Shader *shader, bool gamma = false);
    void draw();

    static unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
};

#endif
