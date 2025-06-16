#include <IGL/GLKeyboard.hpp>
#include <GLFW/glfw3.h>

namespace IGL {

bool GLKeyboard::keys[GLFW_KEY_LAST] { false };
bool GLKeyboard::keysChanged[GLFW_KEY_LAST] { false };

void GLKeyboard::keyCallback(GLFWwindow *window, int keycode, int scancode, int action, int mods) {
    if (action != GLFW_RELEASE && !keys[keycode]) {
        keys[keycode] = true;
    } else
        keys[keycode] = false;

    keysChanged[keycode] = (action != GLFW_REPEAT);
}
    
bool GLKeyboard::key(int keycode) {
    return keys[keycode];
}

bool GLKeyboard::keyChanged(int keycode) {
    bool ret = keysChanged[keycode];
    keysChanged[keycode] = false;
    return ret;
}

bool GLKeyboard::keyWentUp(int keycode) {
    return !keys[keycode] && keyChanged(keycode);
}

bool GLKeyboard::keyWentDown(int keycode) {
    return keys[keycode] && keyChanged(keycode);
}

}
