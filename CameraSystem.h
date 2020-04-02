#pragma once
#include "Misc.h"
#include "Input.h"
#include "SystemBase.h"
#include "World.h"
class CameraSystem : public SystemBase
{
public:
	CameraSystem();

	void OnCreate();

	void OnDestroy();

	void Update();

private:
	unsigned int _CameraMatricesBufferID;
	float _LastX = 0, _LastY = 0, _LastScrollY = 0;
	bool startMouse = false;
	bool startScroll = false;
};