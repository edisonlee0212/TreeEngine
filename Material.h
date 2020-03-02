#ifndef MATERIAL_H
#define MATERIAL_H
class Material {
public:
	Shader* shader;
	vector<Texture> textures;
};
#endif MATERIAL_H
