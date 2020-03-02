#ifndef WORLD_H

#endif // !WORLD_H
#include "EntityManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "CameraManager.h"
#include "WindowManager.h"
#include "ModelManager.h"
class Managers {
public:
	Managers() {
		entityManager = new EntityManager();
		cameraManager = new CameraManager(glm::vec3(0.0f, 0.0f, 3.0f));
		windowManager = new WindowManager();
		timeManager = new TimeManager();
		inputManager = new InputManager();
		modelManager = new ModelManager(entityManager);
	}
	~Managers() {
		delete entityManager;
		delete cameraManager;
		delete windowManager;
		delete timeManager;
		delete inputManager;
	}
	ModelManager* modelManager;
	EntityManager* entityManager;
	CameraManager* cameraManager;
	WindowManager* windowManager;
	InputManager* inputManager;
	TimeManager* timeManager;
};