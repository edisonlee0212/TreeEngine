#pragma once
#include <glfw-3.3/include/GLFW/glfw3.h>
class Input
{
public:
	Input(){
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
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
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
    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
        _CursorMoved = true;
        _CursorX = xpos;
        _CursorY = ypos;
    }
    static void MouseScrollCallback(GLFWwindow* window, double xpos, double ypos) {
        _CursorScrolled = true;
        _CursorScrollX = xpos;
        _CursorScrollY = ypos;
    }
    static bool GetKeyDown(int key) {
        bool down = _KeyDown[key];
        _KeyDown[key] = false;
        return down;
    }
    static bool GetKeyUp(int key) {
        bool up = _KeyUp[key];
        _KeyUp[key] = false;
        return up;
    }
    static bool GetKey(int key) {
        return _KeyPressed[key];
    }
    static bool GetMouseDown(int button) {
        bool down = _MouseDown[button];
        _MouseDown[button] = false;
        return down;
    }
    static bool GetMouseUp(int button) {
        bool up = _MouseUp[button];
        _MouseUp[button] = false;
        return up;
    }
    static bool GetMouse(int button) {
        return _MousePressed[button];
    }
    static glm::vec2 GetMousePosition() {
        return glm::vec2(_CursorX, _CursorY);
    }
    static glm::vec2 GetMouseScroll() {
        return glm::vec2(_CursorScrollX, _CursorScrollY);
    }
    static bool GetMouseScrolled() {
        bool scrolled = _CursorScrolled;
        _CursorScrolled = false;
        return scrolled;
    }
    static bool GetMouseMoved() {
        bool moved = _CursorMoved;
        _CursorMoved = false;
        return moved;
    }

private:
    static bool _KeyPressed[349];
    static bool _KeyDown[349];
    static bool _KeyUp[349];
    static bool _MousePressed[8];
    static bool _MouseDown[8];
    static bool _MouseUp[8];
    static double _CursorX, _CursorY, _CursorScrollX, _CursorScrollY;
    static bool _CursorMoved, _CursorScrolled;
};

double Input::_CursorX, Input::_CursorY, Input::_CursorScrollX, Input::_CursorScrollY;
bool Input::_CursorMoved, Input::_CursorScrolled;
bool Input::_KeyPressed[349];
bool Input::_KeyDown[349];
bool Input::_KeyUp[349];
bool Input::_MousePressed[8];
bool Input::_MouseDown[8];
bool Input::_MouseUp[8];

