#include "Graphics.h"
#include "Default.h"
unsigned int Graphics::Triangles;
unsigned int Graphics::DrawCall;

void Graphics::DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4* matrices, Camera* camera, size_t count) {
	Graphics::DrawCall++;
	Graphics::Triangles += mesh->triangles.size() * count / 3;
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	auto amount = count;
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);
	glBindVertexArray(mesh->VAO());

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glUseProgram(material->shader->ID);
	material->shader->SetFloat("materials[0].shininess", 32.0f);

	material->shader->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
	material->shader->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
	material->shader->SetVec3("lightPos", 0.0f, 1.0f, 0.0f);
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;
	unsigned int normalNr = 0;
	unsigned int heightNr = 0;
	if (material->textures.size() != 0) {
		for (unsigned int i = 0; i < material->textures.size(); i++)
		{
			std::string name = "";
			unsigned int size = -1;
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			switch (material->textures[i]->Type())
			{
			case Material_Type::DIFFUSE:
				size = diffuseNr;
				name = "].diffuse";
				diffuseNr++;
				break;
			case Material_Type::SPECULAR:
				size = specularNr;
				name = "].specular";
				break;
			case Material_Type::NORMAL:
				size = normalNr;
				name = "].normal";
				break;
			case Material_Type::HEIGHT:
				size = heightNr;
				name = "].height";
				break;
			default:
				break;
			}
			// now set the sampler to the correct texture unit
			if(size != -1 && size < Default::ShaderIncludes::MaxMaterialsAmount) material->shader->SetInt("materials[" + std::to_string(size) + name, i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, material->textures[i]->ID());
		}
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(material->shader->ID, "materials[0].diffuse"), 0);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, Default::Textures::MissingTexture->ID());
	}
	// draw mesh

	glDrawElementsInstanced(GL_TRIANGLES, mesh->triangles.size(), GL_UNSIGNED_INT, 0, amount);
	glBindVertexArray(0);
	glDeleteBuffers(1, &buffer);
	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void Graphics::DrawMesh(Mesh* mesh, glm::mat4 matrix, Material* material, Camera* camera) {
	Graphics::DrawCall++;
	Graphics::Triangles += mesh->triangles.size() / 3;
	glUseProgram(material->shader->ID);

	material->shader->SetFloat("materials[0].shininess", 32.0f);
	material->shader->SetMat4("model", matrix);
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;
	unsigned int normalNr = 0;
	unsigned int heightNr = 0;
	if (material->textures.size() != 0) {
		for (unsigned int i = 0; i < material->textures.size(); i++)
		{
			std::string name = "";
			unsigned int size = -1;
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			switch (material->textures[i]->Type())
			{
			case Material_Type::DIFFUSE:
				size = diffuseNr;
				name = "].diffuse";
				diffuseNr++;
				break;
			case Material_Type::SPECULAR:
				size = specularNr;
				name = "].specular";
				break;
			case Material_Type::NORMAL:
				size = normalNr;
				name = "].normal";
				break;
			case Material_Type::HEIGHT:
				size = heightNr;
				name = "].height";
				break;
			default:
				break;
			}
			// now set the sampler to the correct texture unit
			if (size != -1 && size < Default::ShaderIncludes::MaxMaterialsAmount) material->shader->SetInt("materials[" + std::to_string(size) + name, i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, material->textures[i]->ID());
		}
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(material->shader->ID, "materials[0].diffuse"), 0);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, Default::Textures::MissingTexture->ID());
	}
	// draw mesh
	glBindVertexArray(mesh->VAO());
	glDrawElements(GL_TRIANGLES, mesh->triangles.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}
