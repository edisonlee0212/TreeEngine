#ifndef WORLD_H

#endif // !WORLD_H

class Managers {
public:
	Managers() {
		entityManager = new EntityManager();
		cameraManager = new CameraManager(glm::vec3(0.0f, 0.0f, 3.0f));
		windowManager = new WindowManager(800, 600);
		timeManager = new TimeManager();
		inputManager = new InputManager();
	}
	~Managers() {
		delete entityManager;
		delete cameraManager;
		delete windowManager;
		delete timeManager;
		delete inputManager;
	}
	EntityManager* entityManager;
	CameraManager* cameraManager;
	WindowManager* windowManager;
	InputManager* inputManager;
	TimeManager* timeManager;
};