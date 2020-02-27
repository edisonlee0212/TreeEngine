#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "ComponentBase.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Translation.h"
class Entity {
public:
	Mesh* _Mesh;
	Texture* _Texture;
	Shader* _Shader;
	Translation* _Translation;
	int GetKey() { return _Key; }
	Entity(int key)
		: _Key(key)
	{}
private:
	int _Key;
};
#endif ENTITY_H