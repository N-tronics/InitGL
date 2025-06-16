#pragma once

#include <glad/glad.h>
#include <string>

namespace IGL {

class GLShader {
private:
    GLuint shader = 0;
    GLenum type;
    std::string srcFile;
public:
    GLShader(GLenum _type, const std::string& _srcFile);
    ~GLShader();

    const GLuint& getShader() const;
    bool compile(std::string& errors) const;
};

}   // namespace IGL

