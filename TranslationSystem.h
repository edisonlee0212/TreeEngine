#ifndef TRANSLATIONSYSTEM_H
#define TRANSLATIONSYSTEM_H

class TranslationSystem : SystemBase {
public:
    TranslationSystem(Managers* managers) : SystemBase(managers) {
        _SystemType = SystemType::TranslationSystemType;
    }

    void Update();
};

void TranslationSystem::Update() {

}

#endif TRANSLATIONSYSTEM_H

