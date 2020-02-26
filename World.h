#ifndef WORLD_H
#include <vector>
enum SystemType {
	TranslationSystemType,
	CameraSystemType,
	RenderSystemType
};
#include "SystemBase.h"
class World
{
public:
	World();
	void CreateSystem(SystemType type);
	void DestroySystem(SystemType type);
	~World();
	void Update();
private:
	std::vector<SystemBase *> _Systems;
	EntityManager* _EntityManager;
};

World::World()
{
}

World::~World()
{
}

void World::CreateSystem(SystemType type) {
	switch (type)
	{
	case SystemType::RenderSystemType:

		_Systems.push_back(new SystemBase());
		break;
	default:
		break;
	}
}

void World::DestroySystem(SystemType type) {

}

void World::Update() {
	for (auto i : _Systems) {
		if (i->Enabled) i->Update();
	}
}
#endif WORLD_H
