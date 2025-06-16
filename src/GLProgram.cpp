#include <IGL/GLProgram.hpp>
#include <IGL/InitGL.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>

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

GLint GLProgram::getUinformLoc(const std::string identifier) const { return glGetUniformLocation(program, identifier.c_str()); }

bool GLProgram::setUniform1i(const std::string identifier, int value) const {
    GLint loc = getUinformLoc(identifier);
    if (loc == -1)
        return false;
    glUniform1i(loc, value);
    return true;
}

bool GLProgram::setUniform1f(const std::string identifier, float value) const {
    GLint loc = getUinformLoc(identifier);
    if (loc == -1)
        return false;
    glUniform1f(loc, value);
    return true;
}
    
bool GLProgram::setUniformMat4fv(const std::string identifier, glm::mat4 mat) const {
    GLint loc = getUinformLoc(identifier);
    if (loc == -1)
        return false;
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    return true;
}

}   // namespace IGL
