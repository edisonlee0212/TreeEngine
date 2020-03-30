#pragma once
#include <vector>
#include <memory>
class Entity {
public:
	Entity* parent;
	Material* material;
	Mesh* mesh;
	bool ToDraw;
	Entity(unsigned int key) :_Index(key), parent(nullptr) {
		components[typeid(Translation).hash_code()] = (ComponentBase*)malloc(sizeof(Translation));
		components[typeid(Rotation).hash_code()] = (ComponentBase*)malloc(sizeof(Rotation));
		components[typeid(Scale).hash_code()] = (ComponentBase*)malloc(sizeof(Scale));
		components[typeid(LocalToParent).hash_code()] = (ComponentBase*)malloc(sizeof(LocalToParent));
		components[typeid(LocalToWorld).hash_code()] = (ComponentBase*)malloc(sizeof(LocalToWorld));
		ToDraw = false;
	}

	void SetParent(Entity* parent) {
		this->parent = parent;
	}

	~Entity() {
	}
	unsigned int GetKey() { return _Index; }
private:
	std::unordered_map<std::size_t, ComponentBase*> components;
	unsigned int _Index;
	friend class EntityManager;
};