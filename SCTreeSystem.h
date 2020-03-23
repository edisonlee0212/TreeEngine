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
        Mesh* mesh = Default::Primitives::Sphere;
        Material* material = new Material();
        material->shader = new Shader("src/Materials/Shaders/DefaultInstanced.vs", "src/Materials/Shaders/DefaultInstanced.fs"); 
        envelope = new SurfaceOfRevelutionEnvelope(1.0f, 3.0f, 1.0f, -1.0f, 1.0f, -1.0f, mesh, material);
        envelope->SelectPoints(5000);
        Enable();
    }
    void OnDestroy() {
        Disable();
    }
    void Update();
private:
    Envelope* envelope;
    SCTree* tree;
};

void SCTreeSystem::Update() {
    envelope->Draw();
}


#endif SCTRESOURCESYSTEM_H
