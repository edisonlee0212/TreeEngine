#include "World.h"
#include "TRSToLocalToParentSystem.h"
#include "TRSToLocalToWorldSystem.h"
#include "LocalToParentSystem.h"
#include "CameraSystem.h"
#include "RenderSystem.h"
#include "SCTreeSystem.h"
#include "LightingSystem.h"
Camera* World::MainCamera;
EntityManager* World::Entities;

World::World() {
	_DrawSkybox = false;
	_DrawWireframe = false;
	Time::WorldTime = 0;
	Time::DeltaTime = 0;
	Time::LastFrameTime = 0;
	Time::FixedDeltaTime = 0;
	InitMainCamera();
	InitImGui();
	InitSkybox();
	InitEntityManager();
	_TimeStep = 0.2f;

	CreateSystem<TRSToLocalToWorldSystem>();
	CreateSystem<TRSToLocalToParentSystem>();
	CreateSystem<LocalToParentSystem>();
	CreateSystem<CameraSystem>();
	CreateSystem<RenderSystem>();
	CreateSystem<LightingSystem>();
	//CreateSystem<SCTreeSystem>();
}
template <class T>
T* World::CreateSystem() {
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
void World::DestroySystem() {
	for (auto i : _Systems) {
		if (dynamic_cast<T*>(i) != nullptr) {
			i->OnDestroy();
			delete i;
		}
	}
}
template <class T>
T* World::GetSystem() {
	for (auto i : _Systems) {
		if (dynamic_cast<T*>(i) != nullptr) {
			return dynamic_cast<T*>(i);
		}
	}
}
World::~World() {

	for (auto i : _Systems) {
		i->OnDestroy();
		delete i;
	}
	delete Entities;
	delete MainCamera;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void World::Update() {
	float currentFrame = glfwGetTime();
	Time::DeltaTime = currentFrame - Time::LastFrameTime;
	Time::WorldTime += Time::DeltaTime;
	Time::LastFrameTime = currentFrame;
	Time::FixedDeltaTime += Time::DeltaTime;
	Graphics::DrawCall = 0;
	Graphics::Triangles = 0;
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	if (Time::FixedDeltaTime >= _TimeStep) {
		Time::FixedDeltaTime = 0;
		for (auto i : _Systems) {
			if (i->IsEnabled()) i->FixedUpdate();
		}
	}

	for (auto i : _Systems) {
		if (i->IsEnabled()) i->Update();
	}

	if (_DrawSkybox) DrawSkybox();
	DrawInfoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(WindowManager::GetWindow());
}


inline void World::InitEntityManager() {
	Entities = new EntityManager();
}

inline void World::InitImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 420 core");
	ImGui::StyleColorsDark();
}

inline void World::InitMainCamera() {
	MainCamera = new Camera();
}

inline void World::DrawInfoWindow() {
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
	if (ImGui::Button("Draw Skybox")) _DrawSkybox = !_DrawSkybox;
	if (ImGui::Button("Draw Wireframe")) {
		_DrawWireframe = !_DrawWireframe;
		if (_DrawWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	ImGui::End();

	ImGui::Begin("Logs");
	int size = Debug::mLogMessages.size();
	std::string logs = "";
	for (int i = size - 1; i > 0; i--) {
		if (i < size - 50) break;
		logs += *Debug::mLogMessages[i];
	}
	ImGui::Text(logs.c_str());
	ImGui::End();
}

inline void World::InitSkybox() {
	_Skybox = new Texture(Material_Type::DIFFUSE);
	std::vector<std::string> facesPath
	{
		FileSystem::GetPath("Textures/Skyboxes/Default/right.jpg"),
		FileSystem::GetPath("Textures/Skyboxes/Default/left.jpg"),
		FileSystem::GetPath("Textures/Skyboxes/Default/top.jpg"),
		FileSystem::GetPath("Textures/Skyboxes/Default/bottom.jpg"),
		FileSystem::GetPath("Textures/Skyboxes/Default/front.jpg"),
		FileSystem::GetPath("Textures/Skyboxes/Default/back.jpg"),
	};
	_Skybox->LoadCubeMap(facesPath);
	_SkyboxShader = new Shader(FileSystem::GetPath("Shaders/Vertex/Skybox.vert").c_str(), FileSystem::GetPath("Shaders/Fragment/Skybox.frag").c_str());

	glUseProgram(_SkyboxShader->ID);
	_SkyboxShader->SetInt("skybox", 0);

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	// skybox VAO

	glGenVertexArrays(1, &_SkyboxVAO);
	glGenBuffers(1, &_SkyboxVBO);
	glBindVertexArray(_SkyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _SkyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}

inline void World::DrawSkybox() {
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	glUseProgram(_SkyboxShader->ID);
	// skybox cube
	glBindVertexArray(_SkyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _Skybox->ID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}