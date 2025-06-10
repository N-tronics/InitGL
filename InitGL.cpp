#include "InitGL.hpp"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>

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
    initializeGLFW(GL::glfwDefaultErrorCallback, contextVersionMajor, contextVersionMinor);
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

GLFWwindow* GL::getCurrentContext() {
    return glfwGetCurrentContext();
}

void GL::setDisplayFunc(void (*_display)()) {
    display = _display;
}

GLuint GL::createProgram() {
    GLuint program = glCreateProgram();
    if (program == 0) return 0;
    programs.push_back(program);
    return program;
}

void GL::attachShaders(GLuint program, std::vector<ShaderInfo> shaderInfos) {
    GLint status, logLength;

    std::vector<GLuint> shaders;
    for (ShaderInfo shaderInfo : shaderInfos) {
        GLuint shader = glCreateShader(shaderInfo.type);
        if (shader == 0) {
            std::cout << "Loading Shader : " << shaderInfo.srcFile << " Failed." << std::endl;
            exit(1);
        }
        std::ifstream shaderSrc(shaderInfo.srcFile);
        if (!shaderSrc) {
            std::cout << "Cannot open file : " << shaderInfo.srcFile << std::endl;
            exit(1);
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
            std::cout << "Compilation of " << shaderInfo.srcFile << " failed" << std::endl;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            char infoLog[logLength + 1];
            glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
            std::cout << "LOG : " << std::endl << infoLog << std::endl;
            exit(1);
        }

        glAttachShader(program, shader);
        shaders.push_back(shader);
    }

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        std::cout << "Linking of program failed" << std::endl;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        char infoLog[logLength + 1];
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        std::cout << "LOG : " << std::endl << infoLog << std::endl;
        exit(1);
    }
    
    for (GLuint shader : shaders)
        glDeleteShader(shader);
}

void GL::activateProgram(GLuint program) {
    if (!glIsProgram(program)) return;
    glUseProgram(program);
    activeProgram = program;
}

GLuint GL::getActiveProgram() {
    return activeProgram;
}

const std::vector<GLuint>& GL::getPrograms() {
    return programs;
}

void GL::runLoop(GLFWwindow* window) {
    if (!window) {
        if (!currentWindow)
            return;
        else
            window = currentWindow;
    }
    while (!glfwWindowShouldClose(window)) {
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GL::destroyWindow(GLFWwindow* window) {
    if (window == currentWindow)
        currentWindow = NULL;
    glfwDestroyWindow(window);
}

bool GL::setUniform1i(const std::string identifier, int value) {
    GLint loc = glGetUniformLocation(getActiveProgram(), identifier.c_str());
    if (loc == -1)
        return false;
    glUniform1i(loc, value);
    return true;
}

bool GL::setUniform1f(const std::string identifier, float value) {
    GLint loc = glGetUniformLocation(getActiveProgram(), identifier.c_str());
    if (loc == -1)
        return false;
    glUniform1f(loc, value);
    return true;
}

GL::~GL() {
    for (auto program : programs)
        glDeleteProgram(program);
    for (auto window : windows) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}
