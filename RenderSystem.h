#pragma once
#include "Misc.h"
#include "SystemBase.h"
#include "EntityManager.h"
#include "InternalComponents.h"
#include "World.h"
class RenderSystem : public SystemBase
{
public:
	RenderSystem() : SystemBase() {
		

	}

	void OnCreate() {
		Enable();
	}

	void OnDestroy() {
		Disable();
	}
	~RenderSystem();
	void Update();
private:
	
};
