#ifndef RENDERSYSYEM_H
#include <vector>
#include "Renderer.h"
class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
	void addRenderer(Renderer *);
	void Update();
private:
	std::vector<Renderer *> m_renderers;
};


#endif RENDERSYSYEM_H



