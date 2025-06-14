#include "GLMesh.hpp"
#include "__defs__.hpp"
#include "GLProgram.hpp"
#include <GL/gl.h>
#include <cstddef>
#include <iostream>

namespace IGL {

void GLMesh::setupMesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLVertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), BUFFER_OFFSET(offsetof(GLVertex, normal)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLVertex), BUFFER_OFFSET(offsetof(GLVertex, texCoords)));

    glBindVertexArray(0);
}

GLMesh::GLMesh(const std::vector<GLVertex> _vertices, const std::vector<unsigned int> _indices, const std::vector<GLTexture> _textures) {
    vertices = _vertices;
    indices = _indices;
    textures = _textures;

    setupMesh();
}

void GLMesh::draw(const GLProgram& program) {
    unsigned int diffuseNr = 1, specularNr = 1, normalNr = 1, heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        if (name == "texture_specular")
            number = std::to_string(specularNr++);
        if (name == "texture_normal")
            number = std::to_string(normalNr++);
        if (name == "texture_height")
            number = std::to_string(heightNr++);

        program.setUniform1i(name + number, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

}
