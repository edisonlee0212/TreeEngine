#define SPOT_LIGHTS_AMOUNT 4
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

layout (std140, binding = 3) uniform SpotLightBlock
{
    int SpotLightCount;
    SpotLight SpotLights[SPOT_LIGHTS_AMOUNT];
};

