#include "TreeEngine.h"

int main()
{
	TreeEngineStart();
	//LoadNanoSuit(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.3f));
	world->CreateSystem<SCTreeSystem>();
	TreeEngineLoop();
	TreeEngineEnd();
	return 0;
}