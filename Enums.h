#pragma once
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific inputManager methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum Material_Type {
    NONE = 0,
    DIFFUSE = 1,
    SPECULAR = 2,
    AMBIENT = 3,
    EMISSIVE = 4,
    HEIGHT = 5,
    NORMAL = 6,
    SHININESS = 7,
    OPACITY = 8,
    DISPLACEMENT = 9,
    LIGHTMAP = 10,
    REFLECTION = 11,

    BASE_COLOR = 12,
    NORMAL_CAMERA = 13,
    EMISSION_COLOR = 14,
    METALNESS = 15,
    DIFFUSE_ROUGHNESS = 16,
    AMBIENT_OCCLUSION = 17,

    UNKNOWN = 18
};