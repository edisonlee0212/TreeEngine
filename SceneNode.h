#pragma once
#include "Misc.h"
class SceneNode {
public:
	glm::mat4 mTransformation;
	SceneNode* mParent;
	std::vector<SceneNode*> mChildren;
	std::vector<int> mMeshesIndices;
	std::vector<int> mMaterialIndices;
	SceneNode(SceneNode* parent);
	~SceneNode();
};

