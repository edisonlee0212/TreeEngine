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

		material->shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		material->shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		material->shader->setVec3("lightPos", 0.0f, 1.0f, 0.0f);
		material->shader->setVec3("viewPos", camera->Position);
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
		

#pragma region Light
		material->shader->setFloat("material.shininess", 32.0f);

		/*
		   Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		   the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		   by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		   by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		material->shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		material->shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		material->shader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		material->shader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		material->shader->setVec3("pointLights[0].position", glm::vec3(0.7f, 0.2f, 2.0f));
		material->shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		material->shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		material->shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		material->shader->setFloat("pointLights[0].constant", 1.0f);
		material->shader->setFloat("pointLights[0].linear", 0.09);
		material->shader->setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		material->shader->setVec3("pointLights[1].position", glm::vec3(2.3f, -3.3f, -4.0f));
		material->shader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		material->shader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		material->shader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		material->shader->setFloat("pointLights[1].constant", 1.0f);
		material->shader->setFloat("pointLights[1].linear", 0.09);
		material->shader->setFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		material->shader->setVec3("pointLights[2].position", glm::vec3(-4.0f, 2.0f, -12.0f));
		material->shader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		material->shader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		material->shader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		material->shader->setFloat("pointLights[2].constant", 1.0f);
		material->shader->setFloat("pointLights[2].linear", 0.09);
		material->shader->setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		material->shader->setVec3("pointLights[3].position", glm::vec3(0.0f, 0.0f, -3.0f));
		material->shader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		material->shader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		material->shader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		material->shader->setFloat("pointLights[3].constant", 1.0f);
		material->shader->setFloat("pointLights[3].linear", 0.09);
		material->shader->setFloat("pointLights[3].quadratic", 0.032);

		// spotLight
		material->shader->setVec3("spotLight.position", camera->Position);
		material->shader->setVec3("spotLight.direction", camera->Front);
		material->shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		material->shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		material->shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		material->shader->setFloat("spotLight.constant", 1.0f);
		material->shader->setFloat("spotLight.linear", 0.09);
		material->shader->setFloat("spotLight.quadratic", 0.032);
		material->shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		material->shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

#pragma endregion


		material->shader->setVec3("viewPos", camera->Position);
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
				if (name == "material.diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "material.specular")
					number = std::to_string(specularNr++); // transfer unsigned int to stream
				else if (name == "material.normal")
					number = std::to_string(normalNr++); // transfer unsigned int to stream
				else if (name == "material.height")
					number = std::to_string(heightNr++); // transfer unsigned int to stream
				else {
					name = "material.diffuse";
					number = std::to_string(diffuseNr++);
				}
				// now set the sampler to the correct texture unit
				material->shader->setInt((name).c_str(), i);
				// and finally bind the texture
				glBindTexture(GL_TEXTURE_2D, material->textures[i]->ID());
			}
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(glGetUniformLocation(material->shader->ID, "material.diffuse"), 0);
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