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
	CameraSystem(Time * time, EntityManager* entityManager, Window* window) : SystemBase(time, entityManager, window)
	{
		_SystemType = SystemType::CameraSystemType;
		_Camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
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

	}
	Camera* _Camera;
};
#endif CAMERASYSTEM_H