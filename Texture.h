#pragma once
#include "Misc.h"
#include "SharedComponentBase.h"

class Texture : public SharedComponentBase {
public:
    Texture(Material_Type type);

    ~Texture();
    std::size_t hash_code();
    unsigned int ID();
    std::string Path();
    Material_Type Type();
    void Clear();
    void LoadTexture(std::string path, const std::string& directory);
    void LoadCubeMap(std::vector<std::string> faces);
private:
	unsigned int _ID;
    Material_Type _Type;
    std::string _Path;
};