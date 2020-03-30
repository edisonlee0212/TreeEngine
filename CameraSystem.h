#pragma once
class CameraSystem : public SystemBase
{
public:
	CameraSystem() : SystemBase()
	{
	}

	void OnCreate() {
		Enable();
	}

	void OnDestroy() {
		Disable();
	}

	void Update() {
#pragma region Handle Movement

		if (Input::GetKey(GLFW_KEY_W))
			World::MainCamera->ProcessKeyboard(FORWARD, Time::DeltaTime);
		if (Input::GetKey(GLFW_KEY_S))
			World::MainCamera->ProcessKeyboard(BACKWARD, Time::DeltaTime);
		if (Input::GetKey(GLFW_KEY_A))
			World::MainCamera->ProcessKeyboard(LEFT, Time::DeltaTime);
		if (Input::GetKey(GLFW_KEY_D))
			World::MainCamera->ProcessKeyboard(RIGHT, Time::DeltaTime);
		if (Input::GetKey(GLFW_KEY_LEFT_SHIFT))
			World::MainCamera->ProcessKeyboard(UP, Time::DeltaTime);
		if (Input::GetKey(GLFW_KEY_LEFT_CONTROL))
			World::MainCamera->ProcessKeyboard(DOWN, Time::DeltaTime);
#pragma endregion

#pragma region HandleMouse
		auto pos = Input::GetMousePosition();
		if (!startMouse) {
			_LastX = pos.x;
			_LastY = pos.y;
			startMouse = true;
		}
		float xoffset = pos.x - _LastX;
		float yoffset = -pos.y + _LastY;
		_LastX = pos.x;
		_LastY = pos.y;
		if (Input::GetMouse(GLFW_MOUSE_BUTTON_RIGHT)) {
			if (xoffset != 0 || yoffset != 0)World::MainCamera->ProcessMouseMovement(xoffset, yoffset);
			pos = Input::GetMouseScroll();
			if (!startScroll) {
				_LastScrollY = pos.y;
				startScroll = true;
			}
			float yscrolloffset = -pos.y + _LastScrollY;
			_LastScrollY = pos.y;
			if (yscrolloffset != 0)World::MainCamera->ProcessMouseScroll(yscrolloffset);

			
		}
#pragma endregion
		World::MainCamera->UpdateViewProj();
	}

private:
	float _LastX = 0, _LastY = 0, _LastScrollY = 0;
	bool startMouse = false;
	bool startScroll = false;
};