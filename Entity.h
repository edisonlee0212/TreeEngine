#ifndef ENTITY_H
#include <vector>
#include "Component.h"
class Entity {
public:
	std::vector<Component *> _Components;
	int GetKey() { return _Key; }
	Entity(int key)
		: _Key(key)
	{}
private:
	int _Key;
};
#endif ENTITY_H