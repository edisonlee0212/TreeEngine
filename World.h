#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <vector>

double Time::deltaTime;
double Time::lastFrameTime;

class World
{
public:
	World() {
		entityManager = new EntityManager();
		camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	}
	template <class T>
	T* CreateSystem() {
		for (auto i : _Systems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		T* system = new T();
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
		delete entityManager;
		delete camera;

	}
	void Update() {
		float currentFrame = glfwGetTime();
		Time::deltaTime = currentFrame - Time::lastFrameTime;
		Time::lastFrameTime = currentFrame;
		glfwPollEvents();

		for (auto i : _Systems) {
			if (i->IsEnabled()) i->Update();
		}
	}
	static EntityManager* entityManager;
	static Camera* camera;
private:
	std::vector<SystemBase*> _Systems;
};

Camera* World::camera;
EntityManager* World::entityManager;

#endif SYSTEMMANAGER_H
