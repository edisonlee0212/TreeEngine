#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
extern class World;
class CameraSystem : public SystemBase
{
public:

	// Constructor with vectors
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
		if (glfwGetKey(managers->windowManager->window(), GLFW_KEY_W) == GLFW_PRESS)
			managers->cameraManager->ProcessKeyboard(FORWARD, managers->timeManager->deltaTime);
		if (glfwGetKey(managers->windowManager->window(), GLFW_KEY_S) == GLFW_PRESS)
			managers->cameraManager->ProcessKeyboard(BACKWARD, managers->timeManager->deltaTime);
		if (glfwGetKey(managers->windowManager->window(), GLFW_KEY_A) == GLFW_PRESS)
			managers->cameraManager->ProcessKeyboard(LEFT, managers->timeManager->deltaTime);
		if (glfwGetKey(managers->windowManager->window(), GLFW_KEY_D) == GLFW_PRESS)
			managers->cameraManager->ProcessKeyboard(RIGHT, managers->timeManager->deltaTime);
		double xpos, ypos;
		glfwGetCursorPos(managers->windowManager->window(), &xpos, &ypos);
		managers->cameraManager->ProcessMouseMovement(xpos, ypos);
	}
};
#endif CAMERASYSTEM_H