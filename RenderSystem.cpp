#include "RenderSystem.h"


RenderSystem::RenderSystem()
{
	
}

void RenderSystem::addRenderer(Renderer * renderer) {
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