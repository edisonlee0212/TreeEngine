#include "RenderSystem.h"

RenderSystem::RenderSystem() : SystemBase() {
}

void RenderSystem::OnCreate() {
	Enable();
}

void RenderSystem::OnDestroy() {
	Disable();
}

void RenderSystem::Update() {
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	size_t size = World::Entities->GetEntitySize();
	for (size_t i = 0; i < size; i++) {
		Entity* entity = World::Entities->GetEntity(i);
		if (entity->ToDraw) {
			Graphics::DrawMesh(entity->mesh, World::Entities->GetComponent<LocalToWorld>(entity).Value, entity->pointMaterial, World::MainCamera);
		}
	}



}

RenderSystem::~RenderSystem()
{

}