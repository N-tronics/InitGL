#pragma once

#include <GLFW/glfw3.h>

namespace IGL {

class GLKeyboard {
private:
    static bool keys[];
    static bool keysChanged[];
public:
    static void keyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);

    static bool key(int keycode);
    static bool keyChanged(int keycode);
    static bool keyWentUp(int keycode);
    static bool keyWentDown(int keycode);
};

}

