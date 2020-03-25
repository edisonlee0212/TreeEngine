#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <vector>

double Time::deltaTime;
double Time::lastFrameTime;
double Time::fixedDeltaTime;
class World
{
public:
	World() {
		entityManager = new EntityManager();
		camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		_TimeStep = 0.2f;
	}
	template <class T>
	T* CreateSystem() {
		for (auto i : _Systems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		T* system = new T();
		system->OnCreate();
		_Systems.push_back(dynamic_cast<SystemBase*>(system));
		return system;
	}
	template <class T>
	void DestroySystem() {
		for (auto i : _Systems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				i->OnDestroy();
				delete i;
			}
		}
	}
	template <class T>
	T* GetSystem() {
		for (auto i : _Systems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
	}
	~World() {

		for (auto i : _Systems) {
			i->OnDestroy();
			delete i;
		}
		delete entityManager;
		delete camera;
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void Update() {
		float currentFrame = glfwGetTime();
		Time::deltaTime = currentFrame - Time::lastFrameTime;
		Time::lastFrameTime = currentFrame;
		Time::fixedDeltaTime += Time::deltaTime;
		Graphics::DrawCall = 0;
		Graphics::Triangles = 0;
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (Time::fixedDeltaTime >= _TimeStep) {
			Time::fixedDeltaTime = 0;
			for (auto i : _Systems) {
				if (i->IsEnabled()) i->FixedUpdate();
			}
		}

		for (auto i : _Systems) {
			if (i->IsEnabled()) i->Update();
		}

		ImGui::Begin("World Info");
		ImGui::SliderFloat("sec/step", &_TimeStep, 0.05f, 1.0f);
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		int tris = Graphics::Triangles;
		std::string trisstr = "";
		if (tris < 999) {
			trisstr += std::to_string(tris);
		}
		else if (tris < 999999) {
			trisstr += std::to_string((int)(tris / 1000)) + "K";
		}
		else {
			trisstr += std::to_string((int)(tris / 1000000)) + "M";
		}
		trisstr += " tris";
		ImGui::Text(trisstr.c_str());

		ImGui::Text("%d drawcall", Graphics::DrawCall);
		ImGui::End();

		ImGui::Begin("Logs");
		int size = Debug::mLogMessages.size();
		std::string logs = "";
		for (int i = size - 1; i > 0; i--) {
			if (i < size - 50) break;
			logs += Debug::mLogMessages[i];
		}
		ImGui::Text(logs.c_str());
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	static EntityManager* entityManager;
	static Camera* camera;
private:
	std::vector<SystemBase*> _Systems;
	float _TimeStep;
};

Camera* World::camera;
EntityManager* World::entityManager;

#endif SYSTEMMANAGER_H
