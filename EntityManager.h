#pragma once
#include <unordered_map>
#include <utility>
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
	T GetComponent(Entity* entity) {
		T retVal;
		auto search = entity->components.find(typeid(T).hash_code());
		if(search!= entity->components.end()) memcpy(&retVal, search->second, sizeof(T));
		return retVal;
	}

	template <typename T>
	void GetSharedComponent(Entity* entity) {

	}

	template <typename T>
	void SetComponent(Entity* entity, T value) {
		auto search = entity->components.find(typeid(T).hash_code());
		if (search != entity->components.end()) {
			memcpy(search->second, &value, sizeof(T));
			return;
		}
	}
	template <class T>
	void SetSharedComponent(Entity* entity, T value) {
		SharedComponentBase* in = (SharedComponentBase*)value;
		//Get the hashcode of the object class
		auto key = typeid(T).hash_code();
		auto search = _SharedComponentsStorage.find(key);
		if (search != _SharedComponentsStorage.end()) {
			auto insearch = search->second.find(in->hash_code());
			if (insearch != search->second.end()) {
				insearch->second.insert(entity);
			}
			else {
				auto vec = new std::vector<Entity*>();
				vec->push_back(entity);
				auto pair = new std::pair<SharedComponentBase*, std::vector<Entity*>*>(in, vec);
				search->second.insert(in->hash_code(), pair);
			}
		}
		else {
			auto vec = new std::vector<Entity*>();
			vec->push_back(entity);
			auto pair = new std::pair<SharedComponentBase*, std::vector<Entity*>*>(in, vec);
			auto map = new std::unordered_map<std::size_t, std::pair<SharedComponentBase*, std::vector<Entity*>*>>();
			map->insert(in->hash_code(), pair);
			_SharedComponentsStorage.insert(key, map);
		}
	}

	std::vector<Entity*>* GetAllEntities() {
		return &_Entities;
	}
private:
	//<classtypekey, <objkey, pair<obj, entities>>>
	std::unordered_map<std::size_t,
		std::unordered_map<std::size_t,
		std::pair<SharedComponentBase*, std::vector<Entity*>*>*>*> _SharedComponentsStorage;
	std::vector<Entity*> _Entities;
};