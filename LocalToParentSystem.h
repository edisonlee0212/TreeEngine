#pragma once
#include "SystemBase.h"
#include "World.h"
class LocalToParentSystem : public SystemBase {
public:
    LocalToParentSystem();

    void OnCreate();

    void OnDestroy();

    void Update();
};


