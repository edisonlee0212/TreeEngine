#pragma once
class TRSToLocalToParentSystem : public SystemBase {
public:
    TRSToLocalToParentSystem() : SystemBase() {
    }
    void OnCreate() {
        Enable();
    }

    void OnDestroy() {
        Disable();
    }
    void Update();
};

void TRSToLocalToParentSystem::Update() {
    auto entities = World::Entities->GetAllEntities();
    for (auto i : *entities) {
        auto t = World::Entities->GetComponent<Translation>(i);
        auto r = World::Entities->GetComponent<Rotation>(i);
        auto s = World::Entities->GetComponent<Scale>(i);
        if (i->parent != nullptr) {
            LocalToWorld ltw;
            ltw.Value = glm::translate(glm::mat4(1.0f), t.Value);
            ltw.Value = glm::scale(ltw.Value, s.Value);
            World::Entities->SetComponent<LocalToWorld>(i, ltw);
        }
    }
}