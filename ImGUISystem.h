#ifndef IMGUISYSTEM_H
#define IMGUISYSTEM_H

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

#endif IMGUISYSTEM_H

