#pragma once
#include "Misc.h"
#include "Graphics.h"
#include "World.h"
#include "SCBranchRingMesh.h"
class SCBranch {
public:
	Material* mat;
	glm::vec3 position;
	glm::vec3 growDir;
	int growIteration;
	float radius;
	SCBranch* parent;
	std::vector<SCBranch*> mChildren;
	glm::mat4 transform;
	bool hasLeaves;
	bool isTrunk;
	std::vector<SCBranchRingMesh> mRings;
	bool isSubdivided;
	SCBranch(Material* mat, glm::vec3 position, SCBranch* parent, bool isTrunk, int growIteration, float initialRadius = 0.01f);

	~SCBranch();

	void Draw();

	void CollectPoint(std::vector<glm::mat4>* matrices);

	float CalculateRadius(int maxGrowIteration, float n = 3.0f, float minRadius = 0.01f);

	SCBranch* Grow(float growDist, bool growTrunk, glm::vec3 tropism, float distDec = 0.015f, float minDist = 0.1f, float decimationDistChild = 0.05f, float decimationDistParent = 0.05f);

	void Relocation();

	void Subdivision(glm::vec3 fromPos, glm::vec3 fromDir, float fromRadius);

	void CalculateMesh(glm::vec3 rootPos, std::vector<Vertex>* vertices, int resolution = 32);

	void GenerateOrgan(std::vector<glm::mat4>* matrices, int maxGrowIteration, int maxLeaf = 5);
};