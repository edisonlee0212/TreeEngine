#include "Input.h"


double Input::_CursorX, Input::_CursorY, Input::_CursorScrollX, Input::_CursorScrollY;
bool Input::_CursorMoved, Input::_CursorScrolled;
bool Input::_KeyPressed[349];
bool Input::_KeyDown[349];
bool Input::_KeyUp[349];
bool Input::_MousePressed[8];
bool Input::_MouseDown[8];
bool Input::_MouseUp[8];