#include "InitGL.hpp"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace IGL {
bool GL::initializeGLFW(void (*errorCallback)(int, const char*),
                        int contextVersionMajor,
                        int contextVersionMinor
) {
    if (!glfwInit()) {
        return false;
    }
    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

void GL::glfwDefaultErrorCallback(int error, const char* desc) {
    std::cout << "Error (" << error << "): " << desc << std::endl;
    exit(EXIT_FAILURE);
}

GL::GL(int contextVersionMajor, int contextVersionMinor) {
    if (!initializeGLFW(GL::glfwDefaultErrorCallback, contextVersionMajor, contextVersionMinor))
        throw std::runtime_error("Couldn't initialize GLFW.");
}

GLFWwindow *GL::createNewWindow(
    int width, int height,
    const char* title,
    GLFWmonitor *monitor,
    GLFWwindow *share
) {
    GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
    if (!window) {
        std::cout << "GL : Failed to create window" << std::endl;
        return NULL;
    }

    if (windows.empty())
        makeContextCurrent(window);
    
    windows.push_back(window);
    
    return window;
}

void GL::makeContextCurrent(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    currentWindow = window;
}

GLFWwindow* GL::getCurrentContext() { return glfwGetCurrentContext(); }

void GL::setDisplayFunc(void (*_display)(float, float)) { display = _display; }

void GL::setFrameCalculations(void (*_frameCalculations)(float, float)) { frameCalculations = _frameCalculations; }

void GL::registerProgram(const GLProgram& program) {
    if (!glIsProgram(program.getID()))
        throw std::runtime_error("Invalid program to be registered.");
    programs.push_back(program);
}

void GL::useProgram(const GLProgram& program) {
    if (!glIsProgram(program.getID()))
        throw std::runtime_error("Invalid program to be activated.");
    glUseProgram(program.getID());
    activeProgram = program;
}

void GL::useProgram(unsigned int programIdx) {
    if (programIdx >= programs.size())
        throw std::runtime_error("Program index not valid.");
    useProgram(programs[programIdx]);
}

const GLProgram& GL::getActiveProgram() const { return activeProgram; }

const std::vector<GLProgram>& GL::getPrograms() const { return programs; }

void GL::runLoop(GLFWwindow* window) {
    if (!window) {
        if (!currentWindow)
            return;
        else
            window = currentWindow;
    }
    float lastTime = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        if (frameCalculations) frameCalculations(currentTime, deltaTime);
        if (display) display(currentTime, deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GL::destroyWindow(GLFWwindow* window) {
    if (window == currentWindow)
        currentWindow = NULL;
    glfwDestroyWindow(window);
}

GL::~GL() {
    for (auto program : programs)
        glDeleteProgram(program.getID());
    for (auto window : windows) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

}   // namespace IGL
