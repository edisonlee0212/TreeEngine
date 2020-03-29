#include "TreeEngine.h"

int main()
{
	TreeEngineStart();
	//LoadNanoSuit(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.3f));
	 
	auto entity = World::entityManager->CreateEntity();
	Translation translation = Translation();
	translation.Value = glm::vec3(0.0f, -4.0f, 0.0f);
	Scale scale = Scale();
	scale.Value = glm::vec3(1.0f);
	World::entityManager->SetComponent<Translation>(entity, translation);
	World::entityManager->SetComponent<Scale>(entity, scale);
	entity->mesh = Default::Primitives::Sphere;
	auto mat = new Material();
	mat->shader = new Shader("src/Materials/Shaders/Vertex/LightDefault.vert", "src/Materials/Shaders/Fragment/MultipleLights.frag");
	auto texture = new Texture();
	texture->LoadTexture("src/Materials/Textures/white.png", "");



	mat->textures.push_back(texture);
	entity->material = mat;
	entity->ToDraw = true;



	world->CreateSystem<SCTreeSystem>();
	TreeEngineLoop();
	TreeEngineEnd();
	return 0;
}