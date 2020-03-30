#pragma once
#include "Misc.h"
#include "EntityManager.h"
#include "SystemBase.h"
#include "World.h"
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

