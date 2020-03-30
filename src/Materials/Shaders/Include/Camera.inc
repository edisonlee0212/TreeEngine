layout (std140, binding = 0) uniform Camera
{
    mat4 CameraProjection;
    mat4 CameraView;
    vec3 CameraPosition;
};