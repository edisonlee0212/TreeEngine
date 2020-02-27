#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Time.h"
#include "Camera.h"
#include "SystemBase.h"
#include "RenderSystem.h"
#include "CameraSystem.h"
#include "InputSystem.h"
class World
{
public:
	World(Window *);
	void CreateSystem(SystemType type);
	void DestroySystem(SystemType type);
	SystemBase * GetSystem(SystemType type) {
		/*for (auto i : _Systems) {
			if (i->GetSystemType() == type) {
				return i;
			}
		}*/
	}
	~World();
	void Update();
	RenderSystem* _RenderSystem;
	CameraSystem* _CameraSystem;
	InputSystem* _InputSystem;
	EntityManager* _EntityManager = nullptr;
	Window* _Window;
	Time* _Time;
private:
	//std::vector<SystemBase *> _Systems;
	
};

World::World(Window * window)
{
	_EntityManager = new EntityManager();
	_Time = new Time();
	_Window = window;
	_Time->deltaTime = 0.0f;
	_Time->lastFrameTime = 0.0f;
	_RenderSystem = new RenderSystem(_Time, _EntityManager, _Window);
	_CameraSystem = new CameraSystem(_Time, _EntityManager, _Window);
	_InputSystem = new InputSystem(_Time, _EntityManager, _Window);
	_RenderSystem->_Camera = _CameraSystem->_Camera;
}

World::~World()
{
	/*for (auto i : _Systems) {
		delete i;
	}
	delete _EntityManager;*/
}

void World::CreateSystem(SystemType type) {
	/*switch (type)
	{
	case SystemType::RenderSystemType:
		_Systems.push_back((SystemBase*)new RenderSystem(_EntityManager, _Window));
		break;
	case SystemType::CameraSystemType:
		_Systems.push_back((SystemBase*)new CameraSystem(_EntityManager, _Window));
		break;
	case SystemType::InputSystemType:
		_Systems.push_back((SystemBase*)new InputSystem(_EntityManager, _Window));
		break;
	default:
		break;
	}*/
}

void World::DestroySystem(SystemType type) {
	/*for (auto i : _Systems) {
		if (i->GetSystemType() == type) {
			delete i;
		}
	}*/
}

void World::Update() {
	float currentFrame = glfwGetTime();
	_Time->deltaTime = currentFrame - _Time->lastFrameTime;
	_Time->lastFrameTime = currentFrame;
	glfwPollEvents();
	_InputSystem->Update();
	_CameraSystem->Update();
	_RenderSystem->Update();

	/*for (auto i : _Systems) {
		if (i->Enabled) i->Update(deltaTime);
	}*/
}
#endif WORLD_H
