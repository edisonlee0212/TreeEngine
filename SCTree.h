#pragma once
#include "Misc.h"
#include "SCEnvelope.h"
#include "Graphics.h"
#include "SCBranch.h"
class SCTree {
public:
	SCBranch* mRoot;
	std::vector<SCBranch*> mGrowingBranches;
	bool needsToGrow, meshGenerated, organGenerated;
	int maxGrowIteration;
	glm::vec3 position;
	Material* pointMaterial;
	Material* meshMaterial;
	Material* organMaterial;
	std::vector<Mesh*> mMeshList;
	std::vector<glm::mat4> mPointMatrices;
	std::vector<glm::mat4> mLeafList;
	SCTree(glm::vec3 position, Material* pointMaterial, Material* meshMaterial, Material* organMaterial);

	void Draw(bool drawOrgan = true);

	~SCTree();

	void GrowTrunk(float growDist, float attractionDist, SCEnvelope* envelope, glm::vec3 tropism);

	void Grow(float growDist, float attractionDist, float removeDist, SCEnvelope* envelope, glm::vec3 tropism = glm::vec3(0.0f),
		float distDec = 0.015f, float minDist = 0.01f, float decimationDistChild = 0.02f, float decimationDistParent = 0.02f);

	void CalculateMesh(int resolution = 16, int triangleLimit = 8192);
private:
	inline void CalculateRadius();

	inline void CollectPoints();

	inline void NodeRelocation();

	inline void NodeSubdivision();

	inline void GenerateOrgan();
};
