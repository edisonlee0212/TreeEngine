#ifndef IMGUISYSTEM_H
#define IMGUISYSTEM_H

class ImGUISystem : public SystemBase {
public:
	ImGUISystem() : SystemBase() {

	}

	void OnCreate() {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		Enable();
	}

	void OnDestroy() {
		Disable();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void Update() {
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Info");
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

		ImGui::Text("%d tris", Graphics::Triangles);
		ImGui::Text("%d drawcall", Graphics::DrawCall);
		Graphics::DrawCall = 0;
		Graphics::Triangles = 0;
		ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
};

#endif IMGUISYSTEM_H

