#ifndef RENDERSYSYEM_H
#include <vector>
#include "SystemBase.h"
class RenderSystem : public SystemBase
{
public:
	RenderSystem();
	~RenderSystem();
	void addRenderer(Renderer *);
	void Update();
private:
	std::vector<Renderer *> m_renderers;
};


RenderSystem::RenderSystem()
{

}

void RenderSystem::addRenderer(Renderer* renderer) {
	m_renderers.push_back(renderer);
}

void RenderSystem::Update() {
	for (int i = 0; i < m_renderers.size(); i++) {
		m_renderers[i]->render();
	}
}

RenderSystem::~RenderSystem()
{
	for (int i = 0; i < m_renderers.size(); i++) {
		delete m_renderers[i];
	}
	m_renderers.clear();
}

#endif RENDERSYSYEM_H



