#ifndef TRSTOLOCALTOWORLDSYSTEM_H
#define TRSTOLOCALTOWORLDSYSTEM_H

class TRSToLocalToWorldSystem : public SystemBase {
public:
    TRSToLocalToWorldSystem() : SystemBase() {
    }
    void OnCreate() {
        Enable();
    }

    void OnDestroy() {
        Disable();
    }
    void Update();
};

void TRSToLocalToWorldSystem::Update() {
    auto entities = World::entityManager->GetAllEntities();
    for (auto i : *entities) {
        auto t = World::entityManager->GetComponent<Translation>(i);
        auto r = World::entityManager->GetComponent<Rotation>(i);
        auto s = World::entityManager->GetComponent<Scale>(i);
        if (i->parent == nullptr) {
            LocalToWorld ltw;
            ltw.Value = glm::translate(glm::mat4(1.0f), t.Value);
            ltw.Value = glm::scale(ltw.Value, s.Value);
            World::entityManager->SetComponent<LocalToWorld>(i, ltw);
        }
    }
}

#endif TRSTOLOCALTOWORLDSYSTEM_H

