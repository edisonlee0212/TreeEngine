#pragma once
#include "Misc.h"
#include "SystemBase.h"
#include "EntityManager.h"
#include "InternalComponents.h"
#include "World.h"
class RenderSystem : public SystemBase
{
public:
	RenderSystem();

	void OnCreate();

	void OnDestroy();

	~RenderSystem();

	void Update();
private:
	
};
