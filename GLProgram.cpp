#include "GLProgram.hpp"
#include <iostream>
#include <cstdlib>

namespace IGL {

GLProgram::~GLProgram() { glDeleteProgram(program); }
    
GLuint GLProgram::getID() const { return program; }

void GLProgram::use() const { glUseProgram(program); }

void GLProgram::attachShaders(const std::vector<GLShader>& shaders) {
    for (auto shader : shaders)
        attachShader(shader);
}

void GLProgram::attachShader(const GLShader& shader) { 
    if (program == 0) {
        program = glCreateProgram();
        if (program == 0) {
            std::cout << "Couldn't create program" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    glAttachShader(program, shader.getShader());
}

bool GLProgram::link(std::string& errors) const {
    GLint status, logLength;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        std::cout << "Linking of program failed" << std::endl;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        char infoLog[logLength + 1];
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        errors = infoLog;
        return false;
    }

    return true;
}

bool GLProgram::setUniform1i(const std::string identifier, int value) {
    GLint loc = glGetUniformLocation(program, identifier.c_str());
    if (loc == -1)
        return false;
    glUniform1i(loc, value);
    return true;
}

bool GLProgram::setUniform1f(const std::string identifier, float value) {
    GLint loc = glGetUniformLocation(program, identifier.c_str());
    if (loc == -1)
        return false;
    glUniform1f(loc, value);
    return true;
}

}   // namespace IGL
