#ifndef RENDERSYSYEM_H
#define RENDERSYSTEM_H
#include <vector>

#include <glad/include/glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class RenderSystem : public SystemBase
{
public:
	RenderSystem() : SystemBase(){
	}

	void OnCreate() {
		Enable();
	}

	void OnDestroy() {
		Disable();
	}
	~RenderSystem();
	void Update();
};

void RenderSystem::Update() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    size_t size = World::entityManager->GetEntitySize();
    for (size_t i = 0; i < size; i++) {
        Entity* entity = World::entityManager->GetEntity(i);
        if (entity->ToDraw) {
            Graphics::DrawMesh(entity->mesh, World::entityManager->GetComponent<LocalToWorld>(entity).Value, entity->material, World::camera);
        }
    }
}

RenderSystem::~RenderSystem()
{

}

#endif RENDERSYSYEM_H



