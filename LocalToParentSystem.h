#ifndef LOCALTOPARENT_H
#define LOCALTOPARENT_H

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
    auto entities = World::entityManager->GetAllEntities();
    for (auto i : *entities) {
        if (i->parent != nullptr) {
            auto ltp = World::entityManager->GetComponent<LocalToParent>(i).Value;
            auto ltw = World::entityManager->GetComponent<LocalToWorld>(i->parent).Value;
            LocalToWorld in;
            in.Value = ltw * ltp;
            World::entityManager->SetComponent<LocalToWorld>(i, in);
        }
    }
}

#endif LOCALTOPARENT_H

