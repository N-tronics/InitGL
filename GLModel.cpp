#include "GLModel.hpp"
#include <iostream>

namespace IGL {

void GLModel::loadModel(std::string path) {
    Assimp::Importer import;
    std::cout << path << std::endl;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR:ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void GLModel::processNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
        meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
    for (unsigned int i = 0; i < node->mNumChildren; i++) 
        processNode(node->mChildren[i], scene);
}

GLMesh GLModel::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<GLVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GLTexture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        GLVertex v;
        v.position.x = mesh->mVertices[i].x;
        v.position.y = mesh->mVertices[i].y;
        v.position.z = mesh->mVertices[i].z;
        v.normal.x = mesh->mNormals[i].x;
        v.normal.y = mesh->mNormals[i].y;
        v.normal.z = mesh->mNormals[i].z;
        if (mesh->mTextureCoords[0]) {
            v.texCoords.x = mesh->mTextureCoords[0][i].x;
            v.texCoords.y = mesh->mTextureCoords[0][i].y;
        } else {
            v.texCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(v);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<GLTexture> diffuseMaps = loadMaterialTextures(material, 
                                            aiTextureType_DIFFUSE, "texture_diffuse");
        std::vector<GLTexture> specularMaps = loadMaterialTextures(material, 
                                            aiTextureType_SPECULAR, "texture_specular");
        std::vector<GLTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        std::vector<GLTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    } 

    GLMesh m =GLMesh(vertices, indices, textures);
    return m;
}

 std::vector<GLTexture> GLModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<GLTexture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        GLTexture texture;
        bool skip = false;
        for (GLTexture texture : loadedTextures) {
            if (std::strcmp(texture.path.c_str(), str.C_Str()) == 0) {
                textures.push_back(texture);
                skip = true;
                break;
            }
        }
        if (!skip) {
             texture.id = GLModel::textureFromFile(str.C_Str(), directory);
             texture.type = typeName;
             texture.path = str.C_Str();
             textures.push_back(texture);
            loadedTextures.push_back(texture);
        }
    }
    return textures;
}

GLModel::GLModel(std::string path) { loadModel(path); }

GLuint GLModel::textureFromFile(const char* path, const std::string directory, bool gamma) {
    std::string filename(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void GLModel::draw(const GLProgram& program) {
    for (auto mesh : meshes)
        mesh.draw(program);
}

}
