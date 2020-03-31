#pragma once
#include "Misc.h"
#include "InternalComponents.h"
#include "World.h"
#include "Graphics.h"
#include "EntityManager.h"
class ModelManager
{
public:
    ModelManager()
    {
        entities = std::vector<Entity*>();
    }

    static void LoadModel(Entity* root, Shader* shader, std::string const& path, bool gamma = false);
private:
    static std::vector<Entity*> entities;
    static void ProcessNode(std::string, Shader* shader, Entity*, std::vector<Texture*>*, aiNode*, const aiScene*);
    static Entity* ReadMesh(std::string, Shader* shader, std::vector<Texture*>* texturesLoaded, aiMesh* mesh, const aiScene* scene);
    static std::vector<Texture*> LoadMaterialTextures(std::string, std::vector<Texture*>* texturesLoaded, aiMaterial* mat, aiTextureType type, Material_Type typeName);
};

