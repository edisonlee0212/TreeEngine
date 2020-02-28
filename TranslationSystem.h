#ifndef TRANSLATIONSYSTEM_H
#define TRANSLATIONSYSTEM_H

class TranslationSystem : SystemBase {
public:
    TranslationSystem(Camera* camera, Input* input, Time* time, EntityManager* entityManager, Window* window) : SystemBase(camera, input, time, entityManager, window) {
        _SystemType = SystemType::TranslationSystemType;
    }

    void Update();
};

void TranslationSystem::Update() {

}

#endif TRANSLATIONSYSTEM_H

