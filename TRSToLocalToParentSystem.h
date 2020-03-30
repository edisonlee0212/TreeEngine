#pragma once
#include "Misc.h"
#include "SystemBase.h"
#include "World.h"
#include "EntityManager.h"
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
