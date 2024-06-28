#ifndef MODEL_H
#define MODEL_H

#include "../header.h"
#include "./mesh.h"
#include "./shader.h"

using namespace std;


class Model 
{
public:
    // model data 
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;

    Model(string const &path, bool gamma = false);
    void Draw(Shader &shader);

private:
    void loadModel(string const &path);

    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif
