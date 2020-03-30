#pragma once
class Material : public SharedComponentBase{
public:
	~Material() {
		delete shader;
	}
	Shader* shader;
	std::vector<Texture*> textures;
	std::size_t hash_code() { return shader->ID; }
};
