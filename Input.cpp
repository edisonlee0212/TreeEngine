#include "Input.h"


double Input::_CursorX, Input::_CursorY, Input::_CursorScrollX, Input::_CursorScrollY;
bool Input::_CursorMoved, Input::_CursorScrolled;
bool Input::_KeyPressed[349];
bool Input::_KeyDown[349];
bool Input::_KeyUp[349];
bool Input::_MousePressed[8];
bool Input::_MouseDown[8];
bool Input::_MouseUp[8];

Input::Input() {
    for (int i = 0; i < 349; i++) {
        Input::_KeyPressed[i] = false;
        Input::_KeyDown[i] = false;
        _KeyUp[i] = false;
    }
    for (int i = 0; i < 8; i++) {
        Input::_MousePressed[i] = false;
        Input::_MouseDown[i] = false;
        Input::_MouseUp[i] = false;
    }
    Input::_CursorX = Input::_CursorY = Input::_CursorScrollX = Input::_CursorScrollY = 0;
    Input::_CursorMoved = Input::_CursorScrolled = false;
}
void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
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
void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    _CursorMoved = true;
    _CursorX = xpos;
    _CursorY = ypos;
}
void Input::MouseScrollCallback(GLFWwindow* window, double xpos, double ypos) {
    _CursorScrolled = true;
    _CursorScrollX = xpos;
    _CursorScrollY = ypos;
}
bool Input::GetKeyDown(int key) {
    bool down = _KeyDown[key];
    _KeyDown[key] = false;
    return down;
}
bool Input::GetKeyUp(int key) {
    bool up = _KeyUp[key];
    _KeyUp[key] = false;
    return up;
}
bool Input::GetKey(int key) {
    return _KeyPressed[key];
}
bool Input::GetMouseDown(int button) {
    bool down = _MouseDown[button];
    _MouseDown[button] = false;
    return down;
}
bool Input::GetMouseUp(int button) {
    bool up = _MouseUp[button];
    _MouseUp[button] = false;
    return up;
}
bool Input::GetMouse(int button) {
    return _MousePressed[button];
}
glm::vec2 Input::GetMousePosition() {
    return glm::vec2(_CursorX, _CursorY);
}
glm::vec2 Input::GetMouseScroll() {
    return glm::vec2(_CursorScrollX, _CursorScrollY);
}
bool Input::GetMouseScrolled() {
    bool scrolled = _CursorScrolled;
    _CursorScrolled = false;
    return scrolled;
}
bool Input::GetMouseMoved() {
    bool moved = _CursorMoved;
    _CursorMoved = false;
    return moved;
}