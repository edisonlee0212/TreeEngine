#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {

public:
	static unsigned int Triangles;
	static unsigned int DrawCall;
	static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4* matrices, Camera* camera, size_t count) {
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
		material->shader->setMat4("projection", camera->Projection);
		material->shader->setMat4("view", camera->View);
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		if (material->textures.size() != 0) {
			for (unsigned int i = 0; i < material->textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
				// retrieve texture number (the N in diffuse_textureN)
				std::string number;
				std::string name = material->textures[i]->Type();
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "texture_specular")
					number = std::to_string(specularNr++); // transfer unsigned int to stream
				else if (name == "texture_normal")
					number = std::to_string(normalNr++); // transfer unsigned int to stream
				else if (name == "texture_height")
					number = std::to_string(heightNr++); // transfer unsigned int to stream
				else {
					name = "texture_diffuse";
					number = std::to_string(diffuseNr++);
				}
				// now set the sampler to the correct texture unit
				glUniform1i(glGetUniformLocation(material->shader->ID, (name + number).c_str()), i);
				// and finally bind the texture
				glBindTexture(GL_TEXTURE_2D, material->textures[i]->ID());
			}
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(glGetUniformLocation(material->shader->ID, "texture_diffuse1"), 0);
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

	static void DrawMesh(Mesh* mesh, glm::mat4 matrix, Material* material, Camera* camera) {
		Graphics::DrawCall++;
		Graphics::Triangles += mesh->triangles.size() / 3;
		glUseProgram(material->shader->ID);
		material->shader->setMat4("projection", camera->Projection);
		material->shader->setMat4("view", camera->View);
		material->shader->setMat4("model", matrix);
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		if (material->textures.size() != 0) {
			for (unsigned int i = 0; i < material->textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
				// retrieve texture number (the N in diffuse_textureN)
				std::string number;
				std::string name = material->textures[i]->Type();
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "texture_specular")
					number = std::to_string(specularNr++); // transfer unsigned int to stream
				else if (name == "texture_normal")
					number = std::to_string(normalNr++); // transfer unsigned int to stream
				else if (name == "texture_height")
					number = std::to_string(heightNr++); // transfer unsigned int to stream
				else {
					name = "texture_diffuse";
					number = std::to_string(diffuseNr++);
				}
				// now set the sampler to the correct texture unit
				glUniform1i(glGetUniformLocation(material->shader->ID, (name + number).c_str()), i);
				// and finally bind the texture
				glBindTexture(GL_TEXTURE_2D, material->textures[i]->ID());
			}
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(glGetUniformLocation(material->shader->ID, "texture_diffuse1"), 0);
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
};
unsigned int Graphics::Triangles;
unsigned int Graphics::DrawCall;
#endif GRAPHICS_H