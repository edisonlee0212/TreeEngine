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
	void DrawMesh(Mesh* mesh, glm::mat4 matrix, Material* material) {

        glUseProgram(material->shader->ID);

        glm::mat4 projection = glm::perspective(glm::radians(managers->cameraManager->Zoom), (float)managers->windowManager->Width / (float)managers->windowManager->Height, 0.1f, 100.0f);
        glm::mat4 view = managers->cameraManager->GetViewMatrix();
        material->shader->setMat4("projection", projection);
        material->shader->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        material->shader->setMat4("model", matrix);
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < material->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name = material->textures[i].Type();
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(material->shader->ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, material->textures[i].ID());
        }
        // draw mesh
        glBindVertexArray(mesh->VAO());
        glDrawElements(GL_TRIANGLES, mesh->triangles.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
	}
	~RenderSystem();
	void Update();
};

void RenderSystem::Update() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    size_t size = managers->entityManager->GetEntitySize();
    for (int i = 0; i < size; i++) {
        Entity* entity = managers->entityManager->GetEntity(i);
        if (entity->ToDraw) {
            DrawMesh(entity->mesh, entity->GetTransform()->GetLocalToWorld(), entity->material);
        }
    }
	glfwSwapBuffers(managers->windowManager->window());
}

RenderSystem::~RenderSystem()
{

}

#endif RENDERSYSYEM_H



