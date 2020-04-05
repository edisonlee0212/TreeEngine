#pragma once
#include "Misc.h"
#include "SCEnvelope.h"
#include "Graphics.h"
#include "SCBranch.h"
class SCTree {
public:
	SCBranch* mRoot;
	std::vector<SCBranch*> mGrowingBranches;
	bool needsToGrow, meshGenerated;
	int maxGrowIteration;
	glm::vec3 position;
	Material* pointMaterial;
	Material* meshMaterial;
	Mesh* mesh;
	std::vector<glm::mat4> matrices;
	SCTree(glm::vec3 position, Material* pointMaterial, Material* meshMaterial);

	void Draw();

	~SCTree();

	void GrowTrunk(float growDist, float attractionDist, SCEnvelope* envelope, glm::vec3 tropism);

	void Grow(float growDist, float attractionDist, float removeDist, SCEnvelope* envelope, glm::vec3 tropism = glm::vec3(0.0f),
		float distDec = 0.015f, float minDist = 0.01f, float decimationDistChild = 0.02f, float decimationDistParent = 0.02f);

	void CalculateMesh();
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
		mRoot->Subdivision(position, glm::vec3(0.0f, 1.0f, 0.0f), 1);
	}
};
