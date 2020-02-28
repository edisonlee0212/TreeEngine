#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Time.h"
#include "Camera.h"
#include "SystemBase.h"
#include "TranslationSystem.h"
#include "RenderSystem.h"
#include "CameraSystem.h"

class World
{
public:
	World(Camera*, Time*, Window*, Input*);
	void CreateSystem(SystemType type);
	void DestroySystem(SystemType type);
	SystemBase* GetSystem(SystemType type) {
		for (auto i : _Systems) {
			if (i->GetSystemType() == type) {
				return i;
			}
		}
	}
	~World();
	void Update();
	EntityManager* _EntityManager = nullptr;
	Camera* _Camera;
	Window* _Window;
	Input* _Input;
	Time* _Time;
private:
	std::vector<SystemBase*> _Systems;

};

World::World(Camera* camera, Time* time, Window* window, Input* input)
{
	_EntityManager = new EntityManager();
	_Camera = camera;
	_Time = time;
	_Input = input;
	_Window = window;
	_Time->deltaTime = 0.0f;
	_Time->lastFrameTime = 0.0f;
}

World::~World()
{
	for (auto i : _Systems) {
		delete i;
	}
	delete _EntityManager;
}

void World::CreateSystem(SystemType type) {
	switch (type)
	{
	case SystemType::RenderSystemType:
	{
		auto renderSystem = new RenderSystem(_Camera, _Input, _Time, _EntityManager, _Window);
		renderSystem->_Camera = ((CameraSystem*)GetSystem(SystemType::CameraSystemType))->_Camera;
		renderSystem->OnCreate();
		_Systems.push_back((SystemBase*)renderSystem);
	}
	break;
	case SystemType::CameraSystemType:
	{
		auto cameraSystem = new CameraSystem(_Camera, _Input, _Time, _EntityManager, _Window);
		cameraSystem->OnCreate();
		_Systems.push_back((SystemBase*)cameraSystem);
	}
	break;
	}
}

void World::DestroySystem(SystemType type) {
	for (auto i : _Systems) {
		if (i->GetSystemType() == type) {
			i->OnDestroy();
			delete i;
		}
	}
}

void World::Update() {
	float currentFrame = glfwGetTime();
	_Time->deltaTime = currentFrame - _Time->lastFrameTime;
	_Time->lastFrameTime = currentFrame;
	glfwPollEvents();

	for (auto i : _Systems) {
		if (i->IsEnabled()) i->Update();
	}
}
#endif WORLD_H
