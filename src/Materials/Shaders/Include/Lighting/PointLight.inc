#define POINT_LIGHTS_AMOUNT 4
struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


layout (std140, binding = 1) uniform PointsLight
{
    PointLight PointLights[POINT_LIGHTS_AMOUNT];
};