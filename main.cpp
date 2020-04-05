#include "IEngine.h"
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


std::vector<std::vector<int>*>* NextLevel(int level, int min, int max) {
	std::vector<std::vector<int>*>* retVal = new std::vector<std::vector<int>*>();
	if (level == 1) {
		for (int i = min; i <= max; i++) {
			std::vector<int>* tmp = new std::vector<int>();
			tmp->push_back(i);
			retVal->push_back(tmp);
		}
		return retVal;
	}
	int size = max - level + 1;
	for (int i = min; i <= size; i++) {
		std::vector<std::vector<int>*>* tmp = NextLevel(level - 1, i + 1, max);
		for (auto j : *tmp) {
			j->push_back(i);
			retVal->push_back(j);
		}
	}
	return retVal;
}

void InitGround() {
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
	entity->pointMaterial = mat;
	entity->ToDraw = true;
}

int main()
{
	IEngine* engine = new IEngine();
	engine->Start();
	//LoadNanoSuit(glm::vec3(-4.0f, 0.0f, 0.0f), glm::vec3(0.2f));
	

	InitGround();

	

	engine->Loop();
	engine->End();
	
	
	/*
	while (1) {
		int m = 0;
		int n = 0;
		std::cin >> m >> n;
		std::vector<std::vector<int>*> result;
		for (int i = 1; i <= m - n + 1; i++) {
			auto tmp = NextLevel(n - 1, i + 1, m);
			for (auto j : *tmp) {
				j->push_back(i);
				result.push_back(j);
			}
		}
		for (auto i : result) {
			std::string p = "[-";
			for (auto j : *i) p += std::to_string(j) + "-";
			p += "]";
			Debug::Log(p);
		}

		Debug::Log(std::to_string(result.size()));
	}*/
	return 0;
}