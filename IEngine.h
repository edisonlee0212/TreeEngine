#pragma once
#include "Misc.h"
#include "Input.h"

#include "World.h"



#include "ModelManager.h"


class IEngine {
public:
	void GLInit();

	void Start();
	void Loop();
	void End();
private:
	World* world;
	bool _Looping;
};

