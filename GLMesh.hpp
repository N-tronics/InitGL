#pragma once

#include "GLProgram.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <GLFW/glfw3.h>
#include <string>

namespace IGL {

typedef struct _GLVertex {
    glm::vec3 position;  
    glm::vec3 normal;
    glm::vec2 texCoords;
} GLVertex;

typedef struct _GLTexture {
    unsigned int id;
    std::string type;
    std::string path;
} GLTexture;

class GLMesh {
private:
    GLuint vbo = 0, ebo = 0;
    void setupMesh();
public:
    GLuint vao = 0;
    std::vector<GLVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GLTexture> textures;
    
    GLMesh(const std::vector<GLVertex> _vertices, const std::vector<unsigned int> _indices, const std::vector<GLTexture> _textures);
    void draw(const GLProgram& program);
};

}
