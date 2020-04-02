#pragma once
#include "Misc.h"
class Input
{
public:
    Input();
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void MouseScrollCallback(GLFWwindow* window, double xpos, double ypos);
    static bool GetKeyDown(int key);
    static bool GetKeyUp(int key);
    static bool GetKey(int key);
    static bool GetMouseDown(int button);
    static bool GetMouseUp(int button);
    static bool GetMouse(int button);
    static glm::vec2 GetMousePosition();
    static glm::vec2 GetMouseScroll();
    static bool GetMouseScrolled();
    static bool GetMouseMoved();

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


