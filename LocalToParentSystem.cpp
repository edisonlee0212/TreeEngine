#include "LocalToParentSystem.h"

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