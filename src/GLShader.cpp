#include <IGL/GLShader.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace IGL {

GLShader::GLShader(GLenum _type, const std::string& _srcFile) {
    shader = glCreateShader(_type);
    if (shader == 0) {
        std::cout << "Couldn't create shader : " << _type << " : " << _srcFile << std::endl;
        exit(EXIT_FAILURE);
    }
    type = _type;
    srcFile = _srcFile;
}

GLShader::~GLShader() {
    glDeleteShader(shader);
}

const GLuint& GLShader::getShader() const { return shader; }

bool GLShader::compile(std::string& errors) const {
    if (shader == 0) {
        errors = "Shader not created";
        return false;
    }
    GLint status, logLength;
    std::ifstream shaderSrc(srcFile);
    if (!shaderSrc) {
        std::cout << "Cannot open file : " << srcFile << std::endl;
        errors = "Cannot open file : " + srcFile;
        return false;
    }
    std::stringstream ssFileContents;
    for (std::string line; std::getline(shaderSrc, line);)
        ssFileContents << line << "\n";
    shaderSrc.close();
    std::string fileContents = ssFileContents.str();
    
    const char *c_str = fileContents.c_str();
    glShaderSource(shader, 1, &c_str, NULL);

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::cout << "Compilation of " << srcFile << " failed" << std::endl;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        char infoLog[logLength + 1];
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        errors = infoLog;
        return false;
    }

    return true;
}

}
