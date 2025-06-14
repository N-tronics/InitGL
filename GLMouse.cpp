#include "GLMouse.hpp"
#include <GLFW/glfw3.h>

namespace IGL {

double GLMouse::x = 0.0f, GLMouse::y = 0.0f;
double GLMouse::lastX = 0.0f, GLMouse::lastY = 0.0f;
double GLMouse::dx = 0.0f, GLMouse::dy = 0.0f;
double GLMouse::scrollDX = 0.0f, GLMouse::scrollDY = 0.0f;
bool GLMouse::firstMouse = true;
bool GLMouse::buttons[GLFW_MOUSE_BUTTON_LAST] { false };
bool GLMouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] { false };

void GLMouse::posCallback(GLFWwindow *window, double xpos, double ypos) {
    x = xpos;
    y = ypos;

    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    dx = x - lastX;
    dy = lastY - y;
    lastX = x;
    lastY = y;
}

void GLMouse::buttonCallback(GLFWwindow *window, int buttoncode, int action, int mods) {
    if (action != GLFW_RELEASE && !buttons[buttoncode])
        buttons[buttoncode] = true;
    else
        buttons[buttoncode] = false;

    buttonsChanged[buttoncode] = (action != GLFW_REPEAT);
}

void GLMouse::wheelCallback(GLFWwindow *window, double dx, double dy) {
    scrollDX = dx;
    scrollDY = dy;
}

double GLMouse::getX() { return x; }

double GLMouse::getY() { return y; }
    
double GLMouse::getDX() {
    double _dx = dx;
    dx = 0;
    return _dx;
}

double GLMouse::getDY() {
    double _dy = dy;
    dy = 0;
    return _dy;
}

double GLMouse::getScrollDX() {
    double _scrollDX = scrollDX;
    scrollDX = 0;
    return _scrollDX;
}

double GLMouse::getScrollDY() {
    double _scrollDY = scrollDY;
    scrollDY = 0;
    return _scrollDY;
}

bool GLMouse::button(int buttoncode) { return buttons[buttoncode]; }

bool GLMouse::buttonChanged(int buttoncode) {
    bool ret = buttonsChanged[buttoncode];
    buttonsChanged[buttoncode] = false;
    return ret;
}

bool GLMouse::buttonWentUp(int buttoncode) {
    return !buttons[buttoncode] && buttonChanged(buttoncode);
}

bool GLMouse::buttonWentDown(int buttoncode) {
    return buttons[buttoncode] && buttonChanged(buttoncode);
}

}
