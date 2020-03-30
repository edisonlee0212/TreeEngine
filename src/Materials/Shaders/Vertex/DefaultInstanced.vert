#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;

layout (std140, binding = 0) uniform CameraMatrices
{
    mat4 projection;
    mat4 view;
    vec3 viewPos;
};
out vec2 TexCoords;


void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0f); 
}