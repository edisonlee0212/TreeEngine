#pragma once
#include "Misc.h"
#include "SharedComponentBase.h"
#include "Texture.h"
#include "Shader.h"
class Material : public SharedComponentBase{
public:
	Shader* shader;
	std::vector<Texture*> textures;
	~Material();
	std::size_t hash_code();
};
