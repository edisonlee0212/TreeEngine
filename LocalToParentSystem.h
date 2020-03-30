#pragma once
#include "SystemBase.h"
#include "World.h"
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


