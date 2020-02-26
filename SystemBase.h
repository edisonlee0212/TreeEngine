#ifndef SYSTEMBASE_H
#include "EntityManager.h"
class SystemBase {
public:
	bool Enabled;
	EntityManager* GetEntityManager() { return _EntityManager; }
	virtual void OnCreate() {}
	virtual void OnDestroy() {}
	virtual void OnStartRunning() {}
	virtual void OnStopRuning() {}
	virtual void Update() {};
private:
	EntityManager* _EntityManager;
};
#endif SYSTEMBASE_H
