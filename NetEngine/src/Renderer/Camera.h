#pragma once
#ifndef CAMERA_H
#define CAMERA_H
//#include 
#include "../OpenGL/Cube.h"
// Default camera values
const float YAW = 180.0f;
const float PITCH = 30.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float DISTANCE_FROM_PLAYER = 10.0F;
class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera Settings
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float DistanceFromPlayer;
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    // Target Object
    Cube* cube;
    // Constructor
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH, float distance = DISTANCE_FROM_PLAYER)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),
        Zoom(ZOOM), DistanceFromPlayer(distance), cube(nullptr)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    void SetTarget(Cube* currentCube)
    {
        cube = currentCube;
    }
    void Update(float deltaTime)
    {
        if (!cube)
            return;
        float horizontalDistance = calculateHorizontalDistance();
        float verticalDistance = calculateVerticalDistance();
        calculateCameraPosition(horizontalDistance, verticalDistance);
    }
    glm::mat4 GetViewMatrix()
    {
        std::cout << cube->GetPositionX() << std::endl;
        std::cout << cube->GetPositionY() << std::endl;
        std::cout << cube->GetPositionZ() << std::endl;
        return glm::lookAt(Position, cube->GetPosition(), Up);
    }
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        Yaw += xoffset;
        Pitch += yoffset;
        // Clamp Pitch to avoid flipping
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        updateCameraVectors();
    }
private:
    float calculateHorizontalDistance()
    {
        return DistanceFromPlayer * glm::cos(glm::radians(Pitch));
    }
    float calculateVerticalDistance()
    {
        return DistanceFromPlayer * glm::sin(glm::radians(Pitch));
    }
    glm::vec3 calculateCameraPosition(float horizontalDistance, float verticalDistance)
    {
        if (!cube) return glm::vec3(1.0f);
        float xOffset = horizontalDistance * glm::sin(glm::radians(Yaw));
        float zOffset = horizontalDistance * glm::cos(glm::radians(Yaw));
        std::cout << "The X Offset is: " << xOffset << std::endl;
        std::cout << cube->GetPosition().x << std::endl;
        std::cout << cube->GetPosition().z << std::endl;
        Position.x = cube->GetPosition().x - xOffset;
        Position.z = cube->GetPosition().z - zOffset;
        Position.y = cube->GetPosition().y + verticalDistance;
        return Position;
    }


    void updateCameraVectors()
    {
        //// Calculate the new Front vector
        //glm::vec3 front;
        //front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        //front.y = sin(glm::radians(Pitch));
        //front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        //Front = glm::normalize(front);

        // Recalculate Right and Up vectors
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};


#endif