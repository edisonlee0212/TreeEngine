#pragma once
class RenderSystem : public SystemBase
{
public:
	RenderSystem() : SystemBase() {
		

	}

	void OnCreate() {
		Enable();
	}

	void OnDestroy() {
		Disable();
	}
	~RenderSystem();
	void Update();
private:
	
};

void RenderSystem::Update() {
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	size_t size = World::Entities->GetEntitySize();
	for (size_t i = 0; i < size; i++) {
		Entity* entity = World::Entities->GetEntity(i);
		if (entity->ToDraw) {
			Graphics::DrawMesh(entity->mesh, World::Entities->GetComponent<LocalToWorld>(entity).Value, entity->material, World::MainCamera);
		}
	}

	

}

RenderSystem::~RenderSystem()
{

}