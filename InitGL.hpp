#pragma once

#define GLFW_INCLUDE_NONE
#include "gl/gl.h"
#include "GLProgram.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#define BUFFER_OFFSET(offset) ((void*)(offset))

namespace IGL {

class GL {
private:
    std::vector<GLFWwindow*> windows;
    GLFWwindow* currentWindow;
    std::vector<GLProgram> programs;
    GLProgram activeProgram;
    
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
   
    void registerProgram(const GLProgram& program);
    void useProgram(const GLProgram& program);
    void useProgram(unsigned int programIdx);
    
    const GLProgram& getActiveProgram() const;
    const std::vector<GLProgram>& getPrograms() const;
    
    void runLoop(GLFWwindow *window = NULL);
    void destroyWindow(GLFWwindow* window);

    bool setUniform1i(const std::string identifier, int value);
    bool setUniform1f(const std::string identifier, float value);
};

}   // namespace IGL
