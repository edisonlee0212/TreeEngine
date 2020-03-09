#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <vector>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include "Entity.h"
class EntityManager {
public:
	Entity* CreateEntity() {
		Entity* retVal = new Entity(_Entities.size());
		_Entities.push_back(retVal);
		return retVal;
	}

	void DeleteEntity(Entity* entity) {
		int index = entity->_Index;
		_Entities.at(index) = _Entities.back();
		_Entities.pop_back();
		_Entities.at(index)->_Index = index;
		delete entity;
	}
	void DeleteEntity(unsigned int index) {
		Entity* entity = _Entities.at(index);
		_Entities.at(index) = _Entities.back();
		_Entities.pop_back();
		_Entities.at(index)->_Index = index;
		delete entity;
	}

	Entity* GetEntity(unsigned int index) {
		return _Entities.at(index);
	}

	size_t GetEntitySize() {
		return _Entities.size();
	}

	template <typename T>
	void GetComponent(Entity* entity) {

	}

	template <typename T>
	void GetSharedComponent(Entity* entity) {

	}

	template <typename T>
	void SetComponent(Entity* entity, T* value) {
		auto key = typeid(T).hash_code();
		auto search = _SharedComponentsStorage.find(key);
		if (search != _SharedComponentsStorage.end()) {
			SharedComponentBase* in = (SharedComponentBase*)value;
			auto insearch = value->hash_code().find(value->hash_code());
			if (insearch != search->second.end()) {
				_SharedComponentOwners.at(value->hash_code()).insert();
			}
			else {

			}
		}
	}
	template <class T>
	void SetSharedComponent(Entity* entity, T value) {

	}
private:
	std::unordered_map<std::size_t, std::vector<Entity*>> _SharedComponentOwners;
	std::unordered_map<std::size_t, std::unordered_map<std::size_t, SharedComponentBase*>> _SharedComponentsStorage;
	std::vector<Entity *> _Entities;
};
#endif ENTITYMANAGER_H