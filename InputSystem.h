#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include <glfw-3.3/include/GLFW/glfw3.h>
class InputSystem : public SystemBase
{
public:
	InputSystem(Time* time, EntityManager* entityManager = nullptr, Window * window = nullptr) : SystemBase(time, entityManager, window) {
		_SystemType = SystemType::InputSystemType;
	}
	~InputSystem();
	void Update();
	static glm::vec2 GetMousePosition() { return _MousePosition; }
	static glm::vec2 GetMouseOffset() { return _MouseOffset; }
private:
	static glm::vec2 _MousePosition;
	static glm::vec2 _MouseOffset;
};
void InputSystem::Update() {
}

InputSystem::~InputSystem()
{
}
#endif INPUTSYSTEM_H

