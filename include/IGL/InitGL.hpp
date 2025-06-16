#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <IGL/GLProgram.hpp>
#include"__defs__.hpp"
#include <GLFW/glfw3.h>
#include <vector>

namespace IGL {

class GL {
private:
    std::vector<GLFWwindow*> windows;
    GLFWwindow* currentWindow = NULL;
    std::vector<GLProgram> programs;
    
    bool initializeGLFW(void (*errorCallback)(int, const char*),
                        int contextVersionMajor,
                        int contextVersionMinor
    );
    static void glfwDefaultErrorCallback(int error, const char* desc);
    void (*display)(float, float) = NULL;
    void (*frameCalculations)(float, float) = NULL;
    
public:   
    GLProgram activeProgram;
    
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
    void setDisplayFunc(void (*_display)(float, float));
    void setFrameCalculations(void (*_frameCalculations)(float, float));
   
    void registerProgram(const GLProgram& program);
    void useProgram(const GLProgram& program);
    void useProgram(unsigned int programIdx);
    
    const GLProgram& getActiveProgram() const;
    const std::vector<GLProgram>& getPrograms() const;
    
    void runLoop(GLFWwindow *window = NULL);
    void destroyWindow(GLFWwindow* window);
};

}   // namespace IGL
