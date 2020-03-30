#pragma once
#include "SystemBase.h"

class LocalToParentSystem : public SystemBase {
public:
    LocalToParentSystem() : SystemBase() {
    }
    void OnCreate() {
        Enable();
    }

    void OnDestroy() {
        Disable();
    }
    void Update();
};

void LocalToParentSystem::Update() {
    auto entities = World::Entities->GetAllEntities();
    for (auto i : *entities) {
        if (i->parent != nullptr) {
            auto ltp = World::Entities->GetComponent<LocalToParent>(i).Value;
            auto ltw = World::Entities->GetComponent<LocalToWorld>(i->parent).Value;
            LocalToWorld in;
            in.Value = ltw * ltp;
            World::Entities->SetComponent<LocalToWorld>(i, in);
        }
    }
}
