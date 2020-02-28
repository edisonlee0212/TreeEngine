#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CameraSystem : public SystemBase
{
public:

	// Constructor with vectors
	CameraSystem(Camera* camera, Input* input, Time* time, EntityManager* entityManager, Window* window) : SystemBase(camera, input, time, entityManager, window)
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
		if (glfwGetKey(_Window->window(), GLFW_KEY_W) == GLFW_PRESS)
			_Camera->ProcessKeyboard(FORWARD, _Time->deltaTime);
		if (glfwGetKey(_Window->window(), GLFW_KEY_S) == GLFW_PRESS)
			_Camera->ProcessKeyboard(BACKWARD, _Time->deltaTime);
		if (glfwGetKey(_Window->window(), GLFW_KEY_A) == GLFW_PRESS)
			_Camera->ProcessKeyboard(LEFT, _Time->deltaTime);
		if (glfwGetKey(_Window->window(), GLFW_KEY_D) == GLFW_PRESS)
			_Camera->ProcessKeyboard(RIGHT, _Time->deltaTime);
		double xpos, ypos;
		glfwGetCursorPos(_Window->window(), &xpos, &ypos);
		_Camera->ProcessMouseMovement(xpos, ypos);
	}
};
#endif CAMERASYSTEM_H