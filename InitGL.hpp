#pragma once

#define GLFW_INCLUDE_NONE
#include "gl/gl.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <vector>
#include <string>

#define BUFFER_OFFSET(offset) ((void*)(offset))

typedef struct ShaderInfo {
     GLenum type;
     std::string srcFile;
     ShaderInfo(GLenum _type, std::string _srcFile) : type(_type), srcFile(_srcFile) {}
} ShaderInfo;
    
class GL {
private:
    std::vector<GLFWwindow*> windows;
    GLFWwindow* currentWindow;
    std::vector<GLuint> programs;
    GLuint activeProgram = 0;
    
    bool initializeGLFW(void (*errorCallback)(int, const char*),
                        int contextVersionMajor,
                        int contextVersionMinor
    );
    static void glfwDefaultErrorCallback(int error, const char* desc);
    void (*display)();
    
public:   
    
    GL(int contextVersionMajor = 4, int contextVersionMinor = 3);
    ~GL();
    GLFWwindow *createNewWindow(
        int width, int height,
        const char* title,
        GLFWmonitor *monitor,
        GLFWwindow *share
    );
    void makeContextCurrent(GLFWwindow* window);
    GLFWwindow* getCurrentContext();
    void setDisplayFunc(void (*_display)());
    
    GLuint createProgram();
    void attachShaders(GLuint program, std::vector<ShaderInfo> shaderInfos);
    void activateProgram(GLuint program);
    GLuint getActiveProgram();
    const std::vector<GLuint>& getPrograms();
    
    void runLoop(GLFWwindow *window = NULL);
    void destroyWindow(GLFWwindow* window);

    bool setUniform1i(const std::string identifier, int value);
    bool setUniform1f(const std::string identifier, float value);
};
