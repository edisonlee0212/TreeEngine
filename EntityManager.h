#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <vector>
#include <string>
#include "Entity.h"
class EntityManager {
public:
	Entity* AddEntity() {
		Entity* retVal = new Entity(_Entities.size());
		_Entities.push_back(retVal);
		return retVal;
	}
	std::vector<Entity *> _Entities;
};
#endif ENTITYMANAGER_H