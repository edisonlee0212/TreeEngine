#pragma once
#include "Misc.h"
#include "WindowManager.h"
// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes inputManager and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    glm::mat4 Projection;
    glm::mat4 View;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 1.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // Processes inputManager received from any keyboard-like inputManager system. Accepts inputManager parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    
    // Processes inputManager received from a mouse inputManager system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // Processes inputManager received from a mouse scroll-wheel event. Only requires inputManager on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

    void UpdateViewProj();

private:
    // Calculates the front vector from the camera's (updated) Euler Angles
    void UpdateCameraVectors();

};