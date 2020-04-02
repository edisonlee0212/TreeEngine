#include "TreeEngine.h"
#include "Default.h"
void LoadNanoSuit(glm::vec3, glm::vec3);


#pragma region USELESS

void LoadNanoSuit(glm::vec3 position, glm::vec3 scale) {
	Entity* entity = World::Entities->CreateEntity();
	Translation t;
	t.Value = position;
	Scale s;
	s.Value = scale;
	World::Entities->SetComponent<Translation>(entity, t);
	World::Entities->SetComponent<Scale>(entity, s);
	Shader* modelShader = new Shader(FileSystem::GetPath("Shaders/Vertex/LightDefault.vert"), FileSystem::GetPath("Shaders/Fragment/MultipleLights.frag"));
	ModelManager::LoadModel(entity, modelShader, "Resources/Models/nanosuit/nanosuit.obj");
}
#pragma endregion

int main()
{
	TreeEngine* engine = new TreeEngine();
	engine->Start();
	//LoadNanoSuit(glm::vec3(-4.0f, 0.0f, 0.0f), glm::vec3(0.2f));
	auto entity = World::Entities->CreateEntity();
	Translation translation = Translation();
	translation.Value = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale scale = Scale();
	scale.Value = glm::vec3(10.0f);
	World::Entities->SetComponent<Translation>(entity, translation);
	World::Entities->SetComponent<Scale>(entity, scale);
	entity->mesh = Default::Primitives::Quad;
	auto mat = new Material();
	mat->shader = new Shader(FileSystem::GetPath("Shaders/Vertex/LightDefault.vert"), FileSystem::GetPath("Shaders/Fragment/MultipleLights.frag"));
	auto texture = new Texture(Material_Type::DIFFUSE);
	texture->LoadTexture(FileSystem::GetPath("Textures/white.png"), "");



	mat->textures.push_back(texture);
	entity->material = mat;
	entity->ToDraw = true;

	engine->Loop();
	engine->End();
	
	
	return 0;
}