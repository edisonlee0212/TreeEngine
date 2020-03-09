#ifndef MATERIAL_H
#define MATERIAL_H
class Material : public SharedComponentBase{
public:
	Shader* shader;
	std::vector<Texture> textures;
	std::size_t hash_code() { return shader->ID; }
};
#endif MATERIAL_H
