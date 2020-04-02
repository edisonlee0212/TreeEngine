#pragma once
#include "Misc.h"
#include "Scene.h"
#include "SceneNode.h"
#include "Graphics.h"

class AssimpImporter {
public:
    static void LoadScene(Scene* destination, std::string const& path);
private:
    static void ProcessNode(std::string directory, aiNode* node, SceneNode* sceneNode, const aiScene* scene);

    static void ReadMesh(aiMesh* src, Mesh* dest);

    static void ReadMaterial(std::string directory, aiMaterial* src, Material* dest, std::vector<Texture*>* texturesLoaded);

    static inline std::vector<Texture*> LoadMaterialTextures(std::string directory, std::vector<Texture*>* texturesLoaded, aiMaterial* mat, aiTextureType type, Material_Type typeName);
};
