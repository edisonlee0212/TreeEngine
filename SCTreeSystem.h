#ifndef SCTRESOURCESYSTEM_H
#define SCTRESOURCESYSTEM_H
#include "AttractionPointsSet.h"
#include "Envelope.h"
#include "SCTree.h"
#include "SurfaceOfRevolutionEnvelope.h"
class SCTreeSystem : public SystemBase {
public:
    SCTreeSystem() : SystemBase() {
    }
    void OnCreate() {
        growDist = 0.2f;
        attractDitsMult = 3.0f;
        removeDistMult = 0.5f;

        Material* envelopePointMaterial = new Material();
        envelopePointMaterial->shader = new Shader("src/Materials/Shaders/DefaultInstanced.vs", "src/Materials/Shaders/DefaultInstanced.fs"); 
        Texture* envelopeTexture = new Texture();
        envelopeTexture->LoadTexture("src/Materials/Textures/white.png", "");
        envelopePointMaterial->textures.push_back(envelopeTexture);

        envelope = new SurfaceOfRevelutionEnvelope(4.0f, 4.0f, 4.0f, -4.0f, 1.0f, -4.0f, envelopePointMaterial);
        envelope->SelectPoints(1600);
        Material* treeBranchMaterial = new Material();
        treeBranchMaterial->shader = new Shader("src/Materials/Shaders/DefaultInstanced.vs", "src/Materials/Shaders/DefaultInstanced.fs");
        Texture* branchTexture = new Texture();
        branchTexture->LoadTexture("src/Materials/Textures/brown.png", "");
        treeBranchMaterial->textures.push_back(branchTexture);
        tree = new SCTree(glm::vec3(0.0f), treeBranchMaterial);
        attractDits = growDist * attractDitsMult;
        removeDist = growDist * removeDistMult;
        tree->GrowTrunk(growDist, attractDits, envelope, glm::vec3(0.0f));
        Enable();
    }
    void OnDestroy() {
        Disable();
    }
    void Update();

    void FixedUpdate();
private:
    Envelope* envelope;
    SCTree* tree;
    float growDist, attractDitsMult, removeDistMult, attractDits, removeDist;
    bool growComplete;
    
};
void SCTreeSystem::Update() {
    envelope->Draw();
    if (growComplete) {
        tree->Draw();
    }
}
void SCTreeSystem::FixedUpdate() {
    
    if (tree->isGrowing) {
        tree->GrowTreeIteration(growDist, attractDits, removeDist, envelope, glm::vec3(0.0f));
    }
    else if(!growComplete){
        growComplete = true;
        Debug::Log("Grow Complete");
        tree->CollectPoints();
    }
}


#endif SCTRESOURCESYSTEM_H
