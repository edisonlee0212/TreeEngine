#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H
#include "EntityManager.h"
#include "Window.h"
extern class World;
class SystemBase {
public:
	SystemBase(Camera* camera, Input* input, Time* time, EntityManager* entityManagerPtr = nullptr, Window* window = nullptr) : _Camera(camera), _Input(input), _Time(time), _EntityManager(entityManagerPtr), _Window(window) { _Enabled = false; }
	virtual void OnCreate() {}
	virtual void OnDestroy() {}
	virtual void OnStartRunning() {}
	virtual void OnStopRuning() {}
	virtual void Update() = 0;
	EntityManager* GetEntityManager() { return _EntityManager; }
	SystemType GetSystemType() { return _SystemType; }
	void Enable() {
		if (!_Enabled) {
			_Enabled = true;
			OnStartRunning();
		}
	}
	void Disable() {
		if (_Enabled) {
			_Enabled = false;
			OnStopRuning();
		}
	}

	bool IsEnabled() {
		return _Enabled;
	}

public:
	bool _Enabled;
	Camera* _Camera;
	Input* _Input;
	Time* _Time;
	SystemType _SystemType = SystemType::DefaultSystemType;
	EntityManager* _EntityManager;
	Window* _Window;
};
#endif SYSTEMBASE_H
