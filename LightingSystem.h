#pragma once
#include "Misc.h"
#include "SystemBase.h"
#include "Default.h"
struct SpotLight
{
	glm::vec4 position;
	glm::vec4 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
};

struct PointLight
{
	glm::vec4 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
};

struct DirectionalLight
{
	glm::vec4 direction;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
};

class LightingSystem : public SystemBase
{
public:
	LightingSystem();

	void OnCreate() {
		Enable();
	}

	void OnDestroy() {
		Disable();
	}

	~LightingSystem();
	
	void Update();

	int AddSpotLight(SpotLight* data);

	int AddPointLight(PointLight* data);

	int AddDirectionalLight(DirectionalLight* data);
private:
	unsigned int _DirectionalLightBlockID;
	unsigned int _PointLightBlockID;
	unsigned int _SpotLightBlockID;

	std::vector<DirectionalLight> _DirectionalLights;
	std::vector<PointLight> _PointLights;
	std::vector<SpotLight> _SpotLights;

};

