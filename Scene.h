#pragma once
#include "Misc.h"
#include "SceneNode.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

class Scene
{
public:
	std::vector<Mesh*> mMeshes;
	std::vector<Material*> mMaterials;
	std::vector<Texture*> mTextures;
	SceneNode* mRootNode;
	Scene();
	~Scene();
};

