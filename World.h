#pragma once
#include "Misc.h"
#include "Graphics.h"
#include "SystemBase.h"
#include "WindowManager.h"
#include "EntityManager.h"
#include "FileSystem.h"

class World
{
public:
	World();
	template <class T>
	T* CreateSystem();
	template <class T>
	void DestroySystem();
	template <class T>
	T* GetSystem();
	~World();
	void Update();
	static EntityManager* Entities;
	static Camera* MainCamera;
private:
	std::vector<SystemBase*> _Systems;
	float _TimeStep;
	bool _DrawSkybox;
	bool _DrawWireframe;
	Texture* _Skybox;
	Shader* _SkyboxShader;
	unsigned int _SkyboxVAO, _SkyboxVBO;

	inline void InitEntityManager();

	inline void InitImGui();

	inline void InitMainCamera();

	inline void DrawInfoWindow();

	inline void InitSkybox();

	inline void DrawSkybox();
};
