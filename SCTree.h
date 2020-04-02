#pragma once
#include "Misc.h"
#include "SCEnvelope.h"

#include "SCBranch.h"
class SCTree {
public:
	SCBranch* mRoot;
	std::vector<SCBranch*> mGrowingBranches;
	bool needsToGrow;
	int maxGrowIteration;
	glm::vec3 pos;
	Material* material;
	std::vector<glm::mat4> matrices;
	SCTree(glm::vec3 pos, Material* mat);

	void Draw();

	~SCTree();

	void GrowTrunk(float growDist, float attractionDist, SCEnvelope* envelope, glm::vec3 tropism);

	void Grow(float growDist, float attractionDist, float removeDist, SCEnvelope* envelope, glm::vec3 tropism = glm::vec3(0.0f),
		float distDec = 0.015f, float minDist = 0.1f, float decimationDistChild = 0.05f, float decimationDistParent = 0.05f);

	void CalculateMesh(Mesh* mesh);
private:
	inline void CalculateRadius() {
		mRoot->CalculateRadius(maxGrowIteration);
	}

	inline void CollectPoints() {
		matrices.clear();
		mRoot->CollectPoint(&matrices);
	}

	inline void NodeRelocation() {
		Debug::Log("Node Relocation...");
		mRoot->Relocation();
	}

	inline void NodeSubdivision() {
		Debug::Log("Node Subdivision...");
		mRoot->Subdivision(pos, 1);
	}
};
