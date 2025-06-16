#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <IGL/GLMesh.hpp>
#include <stb_image.h>

namespace IGL {

class GLModel {
private:
    std::vector<GLMesh> meshes;
    std::vector<GLTexture> loadedTextures;
    std::string directory;
    bool gammaCorrection;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    GLMesh processMesh(aiMesh *mesh, const aiScene* scene);
    std::vector<GLTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
public:
    GLModel() {}
    GLModel(std::string path);
    
    static GLuint textureFromFile(const char* path, const std::string directory, bool gamma = false);
    void draw(const GLProgram& program);
};

}
