#pragma once
#include "Misc.h"
#include "SystemBase.h"
class ImGUISystem : public SystemBase {
public:
	ImGUISystem() : SystemBase() {

	}

	void OnCreate() {
		// Setup Dear ImGui context
		
		Enable();
	}

	void OnDestroy() {
		Disable();
		
	}
	void Update() {
		// feed inputs to dear imgui, start new frame
		

		

		// Render dear imgui into screen
		
	}
};