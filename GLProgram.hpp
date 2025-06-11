#pragma once

#include "gl/gl.h"
#include "GLShader.hpp"
#include <vector>
#include <string>

namespace IGL {

class GLProgram {
private:
    GLuint program = 0;
public:
    GLProgram() {}
    ~GLProgram();
    
    GLuint getID() const;
    void use() const ;
    void attachShaders(const std::vector<GLShader>& shaders);
    void attachShader(const GLShader& shader);
    bool link(std::string& errors) const;

    bool setUniform1i(const std::string identifier, int value);
    bool setUniform1f(const std::string identifier, float value);
};

}

