#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <vector>


class World
{
public:
	World() {
		managers = new Managers();
	}
	template <class T>
	T* CreateSystem() {
		for (auto i : _Systems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		T* system = new T(managers);
		system->OnCreate();
		_Systems.push_back(dynamic_cast<SystemBase*>(system));
		return system;
	}
	template <class T>
	void DestroySystem() {
		for (auto i : _Systems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				i->OnDestroy();
				delete i;
			}
		}
	}
	template <class T>
	T* GetSystem() {
		for (auto i : _Systems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
	}
	~World() {
		for (auto i : _Systems) {
			i->OnDestroy();
			delete i;
		}
		delete managers;
	}
	void Update() {
		float currentFrame = glfwGetTime();
		managers->timeManager->deltaTime = currentFrame - managers->timeManager->lastFrameTime;
		managers->timeManager->lastFrameTime = currentFrame;
		glfwPollEvents();

		for (auto i : _Systems) {
			if (i->IsEnabled()) i->Update();
		}
	}
	Managers* managers;
private:
	std::vector<SystemBase*> _Systems;
};


#endif SYSTEMMANAGER_H
