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
	RenderSystem(Managers* managers) : SystemBase(managers){
		_SystemType = SystemType::RenderSystemType;
	}

	void OnCreate() {
		Enable();
	}

	void OnDestroy() {
		Disable();
	}

	~RenderSystem();
	void Update();
};

void RenderSystem::Update() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection = glm::perspective((float)glm::radians(managers->cameraManager->Zoom), (float)((float)managers->windowManager->Width / (float)managers->windowManager->Height), 0.1f, 100.0f);
	glm::mat4 view = managers->cameraManager->GetViewMatrix();
	for (auto i : managers->entityManager->_Entities) {
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
	glfwSwapBuffers(managers->windowManager->window());
}

RenderSystem::~RenderSystem()
{

}

#endif RENDERSYSYEM_H



