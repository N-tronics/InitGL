#pragma once

#include <GLFW/glfw3.h>

namespace IGL {

class GLMouse {
private:
    static double x, y;
    static double lastX, lastY;
    static double dx, dy;
    static double scrollDX, scrollDY;
    static bool firstMouse;
    static bool buttons[];
    static bool buttonsChanged[];
public:
    static void posCallback(GLFWwindow *window, double xpos, double ypos);
    static void buttonCallback(GLFWwindow *window, int buttoncode, int action, int mods);
    static void wheelCallback(GLFWwindow *window, double dx, double dy);

    static double getX();
    static double getY();
    
    static double getDX();
    static double getDY();

    static double getScrollDX();
    static double getScrollDY();

    static bool button(int buttoncode);
    static bool buttonChanged(int buttoncode);
    static bool buttonWentUp(int buttoncode);
    static bool buttonWentDown(int buttoncode);
};
    
}
