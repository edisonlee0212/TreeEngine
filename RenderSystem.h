#ifndef RENDERSYSYEM_H
#define RENDERSYSTEM_H
#include <vector>

#include <glad/include/glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class RenderSystem : public SystemBase
{
public:
	RenderSystem(Time* time, EntityManager* entityManager = nullptr, Window* window = nullptr) : SystemBase(time, entityManager, window) {
		_SystemType = SystemType::RenderSystemType;
	}
	~RenderSystem();
	void Update();
	Camera* _Camera;
};

void RenderSystem::Update() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection = glm::perspective(glm::radians(_Camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = _Camera->GetViewMatrix();
	for (auto i : _EntityManager->_Entities) {
		glUseProgram(i->_Shader->ID);
		i->_Shader->setInt("texture1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, i->_Texture->_Index);
		i->_Shader->setMat4("projection", projection);
		i->_Shader->setMat4("view", view);
		i->_Shader->setMat4("model", i->_Translation->_Value);

		glBindVertexArray(i->_Mesh->_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glfwSwapBuffers(_Window->window());
}

RenderSystem::~RenderSystem()
{

}

#endif RENDERSYSYEM_H



