#include "Material.h"

std::size_t Material::hash_code() { return shader->ID; }

Material::~Material() {
	delete shader;
}