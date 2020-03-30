#pragma once
#include "Misc.h"
#include "SharedComponentBase.h"
#include "Texture.h"
#include "Shader.h"
class Material : public SharedComponentBase{
public:
	~Material() {
		delete shader;
	}
	Shader* shader;
	std::vector<Texture*> textures;
	std::size_t hash_code() { return shader->ID; }
};
