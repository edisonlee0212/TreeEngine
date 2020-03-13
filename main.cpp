#include "TreeEngine.h"



int main()
{
	TreeEngineStart();
	//For testing complex mesh model purpose, model downloaded from internet.
	LoadNanoSuit(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.3f, 0.3f, 0.3f));

	world->CreateSystem<SCTResourceSystem>();
	TreeEngineLoop();
	TreeEngineEnd();
	return 0;
}

void TreeEngineLoop() {
	while (!glfwWindowShouldClose(WindowManager::GetWindow()))
	{
		world->Update();
		glfwSwapBuffers(WindowManager::GetWindow());
	}
}