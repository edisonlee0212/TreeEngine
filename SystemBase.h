#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H
#include "EntityManager.h"
#include "Window.h"
extern class World;
class SystemBase {
public:
	bool Enabled;
	SystemBase(Time * time, EntityManager* entityManagerPtr = nullptr, Window * window = nullptr) : _Time(time), _EntityManager(entityManagerPtr), _Window(window) {}
	virtual void OnCreate() {}
	virtual void OnDestroy() {}
	virtual void OnStartRunning() {}
	virtual void OnStopRuning() {}
	virtual void Update() = 0;
	EntityManager* GetEntityManager() { return _EntityManager; }
	SystemType GetSystemType() { return _SystemType; }
public:
	Time* _Time;
	SystemType _SystemType = SystemType::DefaultSystemType;
	EntityManager* _EntityManager;
	Window* _Window;
};
#endif SYSTEMBASE_H
