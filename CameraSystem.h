#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class CameraSystem : public SystemBase
{
public:
	CameraSystem(Managers* managers) : SystemBase(managers)
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
		if (managers->inputManager->GetKey(GLFW_KEY_W))
			managers->cameraManager->ProcessKeyboard(FORWARD, managers->timeManager->deltaTime);
		if (managers->inputManager->GetKey(GLFW_KEY_S))
			managers->cameraManager->ProcessKeyboard(BACKWARD, managers->timeManager->deltaTime);
		if (managers->inputManager->GetKey(GLFW_KEY_A))
			managers->cameraManager->ProcessKeyboard(LEFT, managers->timeManager->deltaTime);
		if (managers->inputManager->GetKey(GLFW_KEY_D))
			managers->cameraManager->ProcessKeyboard(RIGHT, managers->timeManager->deltaTime);

		auto pos = managers->inputManager->GetMousePosition();
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
		if (xoffset != 0 || yoffset != 0)managers->cameraManager->ProcessMouseMovement(xoffset, yoffset);

		pos = managers->inputManager->GetMouseScroll();

		if (!startScroll) {
			_LastScrollY = pos.y;
			startScroll = true;
		}
		float yscrolloffset = -pos.y + _LastScrollY;
		_LastScrollY = pos.y;
		if (yscrolloffset != 0)managers->cameraManager->ProcessMouseScroll(yscrolloffset);
#pragma endregion
	}

private:
	float _LastX, _LastY, _LastScrollY;
	bool startMouse = false;
	bool startScroll = false;
};
#endif CAMERASYSTEM_H