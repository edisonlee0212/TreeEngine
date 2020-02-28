#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include <glfw-3.3/include/GLFW/glfw3.h>
class InputManager
{
public:
	InputManager(){
	}
	void KeyCallback(GLFWwindow*, int, int, int, int);
    void MouseButtonCallback(GLFWwindow*, int, int, int);
    void CursorPositionCallback(GLFWwindow*, double, double);
    void MouseScrollCallback(GLFWwindow* window, double, double);
    bool GetKeyDown(int scancode) {
        bool down = _KeyDown[scancode];
        _KeyDown[scancode] = false;
        return down;
    }
    bool GetKeyUp(int scancode) {
        bool up = _KeyUp[scancode];
        _KeyUp[scancode] = false;
        return up;
    }
    bool GetKey(int scancode) {
        return _KeyPressed[scancode];
    }
    bool GetMouseDown(int scancode) {
        bool down = _MouseDown[scancode];
        _MouseDown[scancode] = false;
        return down;
    }
    bool GetMouseUp(int scancode) {
        bool up = _MouseUp[scancode];
        _MouseUp[scancode] = false;
        return up;
    }
    bool GetMouse(int scancode) {
        return _MousePressed[scancode];
    }
    glm::vec2 GetMousePosition() {
        return glm::vec2(_CursorX, _CursorY);
    }
    glm::vec2 GetMouseScroll() {
        return glm::vec2(_CursorScrollX, _CursorScrollY);
    }
    bool GetMouseScrolled() {
        bool scrolled = _CursorScrolled;
        _CursorScrolled = false;
        return scrolled;
    }
    bool GetMouseMoved() {
        bool moved = _CursorMoved;
        _CursorMoved = false;
        return moved;
    }

private:
    bool _KeyPressed[349];
    bool _KeyDown[349];
    bool _KeyUp[349];
    bool _MousePressed[8];
    bool _MouseDown[8];
    bool _MouseUp[8];
    double _CursorX, _CursorY, _CursorScrollX, _CursorScrollY;
    bool _CursorMoved, _CursorScrolled;
};
void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UNKNOWN) return;
    if (action == GLFW_PRESS) {
        _KeyPressed[key] = true;
        _KeyDown[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        _KeyPressed[key] = false;
        _KeyUp[key] = true;
    }
}

void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_KEY_UNKNOWN) return;
    if (action == GLFW_PRESS) {
        _MousePressed[button] = true;
        _MouseDown[button] = true;
    }
    else if (action == GLFW_RELEASE) {
        _MousePressed[button] = false;
        _MouseUp[button] = true;
    }
}

void InputManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    _CursorMoved = true;
    _CursorX = xpos;
    _CursorY = ypos;
}

void InputManager::MouseScrollCallback(GLFWwindow* window, double xpos, double ypos) {
    _CursorScrolled = true;
    _CursorScrollX = xpos;
    _CursorScrollY = ypos;
}
#endif INPUTSYSTEM_H

