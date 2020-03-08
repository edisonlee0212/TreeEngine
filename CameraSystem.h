#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CameraSystem : public SystemBase
{
public:
	CameraSystem() : SystemBase()
	{
		_SystemType = SystemType::CameraSystemType;
	}

	void OnCreate(){
		Enable();
	}

	void OnDestroy() {
		Disable();
	}

	void Update() {
		#pragma region Handle Movement
		if (Input::GetKey(GLFW_KEY_W))
			World::camera->ProcessKeyboard(FORWARD, Time::deltaTime);
		if (Input::GetKey(GLFW_KEY_S))
			World::camera->ProcessKeyboard(BACKWARD, Time::deltaTime);
		if (Input::GetKey(GLFW_KEY_A))
			World::camera->ProcessKeyboard(LEFT, Time::deltaTime);
		if (Input::GetKey(GLFW_KEY_D))
			World::camera->ProcessKeyboard(RIGHT, Time::deltaTime);

		auto pos = Input::GetMousePosition();
		#pragma endregion

		#pragma region HandleMouse
		if (!startMouse) {
			_LastX = pos.x;
			_LastY = pos.y;
			startMouse = true;
		}
		float xoffset = pos.x - _LastX;
		float yoffset = -pos.y + _LastY;
		_LastX = pos.x;
		_LastY = pos.y;
		if (xoffset != 0 || yoffset != 0)World::camera->ProcessMouseMovement(xoffset, yoffset);

		pos = Input::GetMouseScroll();

		if (!startScroll) {
			_LastScrollY = pos.y;
			startScroll = true;
		}
		float yscrolloffset = -pos.y + _LastScrollY;
		_LastScrollY = pos.y;
		if (yscrolloffset != 0)World::camera->ProcessMouseScroll(yscrolloffset);
#pragma endregion
	}

private:
	float _LastX = 0, _LastY = 0, _LastScrollY = 0;
	bool startMouse = false;
	bool startScroll = false;
};
#endif CAMERASYSTEM_H