#include "CameraSystem.h"
CameraSystem::CameraSystem() : SystemBase()
{
	glGenBuffers(1, &_CameraMatricesBufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, _CameraMatricesBufferID, 0, 2 * sizeof(glm::mat4));
}

void CameraSystem::OnCreate() {
	Enable();
}

void CameraSystem::OnDestroy() {
	Disable();
}

void CameraSystem::Update() {
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

	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(World::MainCamera->Projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(World::MainCamera->View));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, _CameraMatricesBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(World::MainCamera->Position));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}