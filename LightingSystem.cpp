#include "LightingSystem.h"

LightingSystem::LightingSystem() : SystemBase() {
	_DirectionalLights = std::vector<DirectionalLight>();
	_PointLights = std::vector<PointLight>();
	_SpotLights = std::vector<SpotLight>();

	size_t size = 16 + Default::ShaderIncludes::MaxDirectionalLightAmount * sizeof(DirectionalLight);
	glGenBuffers(1, &_DirectionalLightBlockID);
	glBindBuffer(GL_UNIFORM_BUFFER, _DirectionalLightBlockID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _DirectionalLightBlockID);
	// or
	//glBindBufferRange(GL_UNIFORM_BUFFER, 1, _DirectionalLightBlockID, 0, size);
	size = 16 + Default::ShaderIncludes::MaxPointLightAmount * sizeof(PointLight);
	glGenBuffers(1, &_PointLightBlockID);
	glBindBuffer(GL_UNIFORM_BUFFER, _PointLightBlockID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, _PointLightBlockID);

	size = 16 + Default::ShaderIncludes::MaxSpotLightAmount * sizeof(SpotLight);
	glGenBuffers(1, &_SpotLightBlockID);
	glBindBuffer(GL_UNIFORM_BUFFER, _SpotLightBlockID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, _SpotLightBlockID);

	DirectionalLight dl = DirectionalLight();
	dl.direction = glm::vec4(0.0f, -1.0f, 0.5f, 0.0f);
	dl.ambient = glm::vec4(0.1f);
	dl.diffuse = glm::vec4(0.4f);
	dl.specular = glm::vec4(0.5f);
	AddDirectionalLight(&dl);
	/*PointLight pl = PointLight();
	pl.position = glm::vec4(0.7f, 0.2f, 2.0f, 0.0f);
	pl.ambient = glm::vec4(0.05f);
	pl.diffuse = glm::vec4(0.8f);
	pl.specular = glm::vec4(1.0f);
	pl.constant = 1.0f;
	pl.linear = 0.09f;
	pl.quadratic = 0.032f;
	
	//AddPointLight(&pl);
	pl.position = glm::vec4(2.3f, -3.3f, -4.0f, 0.0f);
	//AddPointLight(&pl);
	pl.position = glm::vec4(4.0f, 2.0f, -12.0f, 0.0f);
	//AddPointLight(&pl);
	pl.position = glm::vec4(0.0f, 0.0f, -3.0f, 0.0f);
	//AddPointLight(&pl);*/
}

void LightingSystem::Update() {

	auto dl = _DirectionalLights[0];
	dl.direction = glm::vec4(0.0f, -glm::abs(glm::sin(Time::WorldTime / 2.0f)), glm::cos(Time::WorldTime / 2.0f), 0.0f);
	_DirectionalLights[0] = dl;
	glBindBuffer(GL_UNIFORM_BUFFER, _DirectionalLightBlockID);
	size_t size = _DirectionalLights.size();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 4, &size);
	size = size * sizeof(DirectionalLight);
	if (size != 0)glBufferSubData(GL_UNIFORM_BUFFER, 16, size, &_DirectionalLights[0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, _PointLightBlockID);
	size = _PointLights.size();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 4, &size);
	size = size * sizeof(PointLight);
	if (size != 0)glBufferSubData(GL_UNIFORM_BUFFER, 16, size, &_PointLights[0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, _SpotLightBlockID);
	size = _SpotLights.size();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 4, &size);
	size = size * sizeof(SpotLight);
	if (size != 0)glBufferSubData(GL_UNIFORM_BUFFER, 16, size, &_SpotLights[0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

int LightingSystem::AddDirectionalLight(DirectionalLight* data) {
	if (_DirectionalLights.size() >= Default::ShaderIncludes::MaxDirectionalLightAmount) {
		Debug::Error("LightingSystem: Directional light out of limit!");
		return -1;
	}
	_DirectionalLights.push_back(*data);
	return _DirectionalLights.size() - 1;
}

int LightingSystem::AddPointLight(PointLight* data) {
	if (_PointLights.size() >= Default::ShaderIncludes::MaxPointLightAmount) {
		Debug::Error("LightingSystem: Point light out of limit!");
		return -1;
	}
	_PointLights.push_back(*data);
	return _PointLights.size() - 1;
}

int LightingSystem::AddSpotLight(SpotLight* data) {
	if (_SpotLights.size() >= Default::ShaderIncludes::MaxSpotLightAmount) {
		Debug::Error("LightingSystem: Spot light out of limit!");
		return -1;
	}
	_SpotLights.push_back(*data);
	return _SpotLights.size() - 1;
}


LightingSystem::~LightingSystem() {

}