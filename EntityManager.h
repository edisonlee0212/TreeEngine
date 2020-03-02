#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <vector>
#include <string>
#include "Entity.h"
class EntityManager {
public:
	Entity* CreateEntity() {
		Entity* retVal = new Entity(_Entities.size());
		_Entities.push_back(retVal);
		return retVal;
	}
	Entity* GetEntity(unsigned int key) {
		return _Entities.at(key);
	}

	size_t GetEntitySize() {
		return _Entities.size();
	}
private:
	std::vector<Entity *> _Entities;
};
#endif ENTITYMANAGER_H