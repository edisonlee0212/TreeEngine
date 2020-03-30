#pragma once

class SceneNode {
public:
	glm::mat4 mTransformation;
	SceneNode* mParent;
	std::vector<SceneNode *> mChildren;
	std::vector<int> mMeshesIndices;
	std::vector<int> mMaterialIndices;
	SceneNode(SceneNode * parent) : mParent(parent){}
	~SceneNode() {
		for (auto i : mChildren) delete i;
		mChildren.clear();
	}
};
class Scene
{
public:
	std::vector<Mesh*> mMeshes;
	std::vector<Material*> mMaterials;
	std::vector<Texture*> mTextures;
	SceneNode* mRootNode;
	Scene() {
		mRootNode = new SceneNode(nullptr);
	}
	~Scene() {
		delete mRootNode;
		for (auto i : mMeshes) delete i;
		for (auto i : mMaterials) delete i;
		for (auto i : mTextures) delete i;
		mMeshes.clear();
		mMaterials.clear();
		mTextures.clear();
	}
};

