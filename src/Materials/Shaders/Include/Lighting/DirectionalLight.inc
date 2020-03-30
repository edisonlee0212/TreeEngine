#define DIRECTIONAL_LIGHTS_AMOUNT 4
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout (std140, binding = 1) uniform DirectionalLights
{
    DirectionalLight DirectionalLights[DIRECTIONAL_LIGHTS_AMOUNT];
};