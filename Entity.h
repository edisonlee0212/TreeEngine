#ifndef ENTITY_H
#define ENTITY_H
#include <vector>

class Entity {
public:
	Translation translation;
	Rotation rotation;
	Scale scale;
	LocalToParent localToParent;
	LocalToWorld localToWorld;

	Entity* _Parent;
	Material* material;
	Mesh* mesh;
	bool ToDraw;
	Entity(unsigned int key) :_Index(key) {
		_Transform = new Transform();
		ToDraw = false;
	}
	Transform* GetTransform() {
		return _Transform;
	}
	~Entity() {
		delete _Transform;
	}
	unsigned int GetKey() { return _Index; }
private:
	unsigned int _Index;
	Transform* _Transform;
	friend class EntityManager;
};
#endif ENTITY_H