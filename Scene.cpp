#include "Scene.h"

SceneNode::SceneNode(SceneNode* parent) : mParent(parent) {}
SceneNode::~SceneNode() {
	for (auto i : mChildren) delete i;
	mChildren.clear();
}

Scene::Scene() {
	mRootNode = new SceneNode(nullptr);
}
Scene::~Scene() {
	delete mRootNode;
	for (auto i : mMeshes) delete i;
	for (auto i : mMaterials) delete i;
	for (auto i : mTextures) delete i;
	mMeshes.clear();
	mMaterials.clear();
	mTextures.clear();
}