#ifndef SCTRESOURCESYSTEM_H
#define SCTRESOURCESYSTEM_H
#include "SCEnvelope.h"
#include "SCTree.h"
#include "SurfaceOfRevolutionEnvelope.h"
class SCTreeSystem : public SystemBase {
public:
	SCTreeSystem() : SystemBase() {
	}
	void OnCreate() {
		_Iteration = 0;
		envelopePointMaterial = new Material();
		envelopePointMaterial->shader = new Shader("src/Materials/Shaders/DefaultInstanced.vs", "src/Materials/Shaders/DefaultInstanced.fs");
		envelopeTexture = new Texture();
		envelopeTexture->LoadTexture("src/Materials/Textures/white.png", "");
		envelopePointMaterial->textures.push_back(envelopeTexture);

		treeBranchMaterial = new Material();
		treeBranchMaterial->shader = new Shader("src/Materials/Shaders/DefaultInstanced.vs", "src/Materials/Shaders/DefaultInstanced.fs");
		branchTexture = new Texture();
		branchTexture->LoadTexture("src/Materials/Textures/brown.png", "");
		treeBranchMaterial->textures.push_back(branchTexture);

		envelope = new SurfaceOfRevelutionEnvelope(4.0f, 4.0f, 4.0f, -4.0f, 1.0f, -4.0f, envelopePointMaterial);

		tree = new SCTree(glm::vec3(0.0f), treeBranchMaterial);
		Debug::Log("Generating attraction points...");
		envelope->GeneratePoints(1600);
		Debug::Log("Attraction points generation complete. [Amount: " + std::to_string(1600) + "]");
		growDist = 0.3f;
		attractDitsMult = 3.0f;
		removeDistMult = 0.5f;
		attractDits = growDist * attractDitsMult;
		removeDist = growDist * removeDistMult;
		Debug::Log("Trunk growing...");
		tree->GrowTrunk(growDist, attractDits, envelope, glm::vec3(0.0f));
		Debug::Log("Trunk grow complete.");
		Enable();
	}
	void OnDestroy() {
		Disable();
		delete envelopePointMaterial;
		delete envelopeTexture;
		delete treeBranchMaterial;
		delete branchTexture;
	}
	void Update();

	void FixedUpdate();
private:
	Material* envelopePointMaterial;
	Texture* envelopeTexture;
	Material* treeBranchMaterial;
	Texture* branchTexture;
	SCEnvelope* envelope;
	SCTree* tree;
	float growDist, attractDitsMult, removeDistMult, attractDits, removeDist;
	int _Iteration;
};
void SCTreeSystem::Update() {
	envelope->Draw();
	tree->Draw();
}
void SCTreeSystem::FixedUpdate() {
	if (tree->needsToGrow) {
		_Iteration++;
		Debug::Log("Growing... [Iteration: " + std::to_string(_Iteration) + "]");
		tree->Grow(growDist, attractDits, removeDist, envelope);
	}
}


#endif SCTRESOURCESYSTEM_H
