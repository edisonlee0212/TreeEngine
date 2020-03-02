#ifndef ENTITY_H
#define ENTITY_H
#include <vector>

class Entity {
public:
	Entity* parent;
	Material* material;
	Mesh* mesh;
	bool ToDraw;
	Entity(unsigned int key) :_Key(key) {
		_Transform = new Transform();
		ToDraw = false;
	}
	Transform* GetTransform() {
		return _Transform;
	}
	~Entity() {
		delete _Transform;
	}
private:
	unsigned int _Key;
	Transform* _Transform;
};
#endif ENTITY_H