#include "TreeEngine.h"

int main()
{
	TreeEngineStart();
	world->CreateSystem<SCTResourceSystem>();
	TreeEngineLoop();
	TreeEngineEnd();
	return 0;
}