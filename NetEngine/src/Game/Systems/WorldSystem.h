#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Renderer/Shader.h"

#define RUN_SPEED 3
#define TURN_SPEED 160

class WorldSystem
{
public:
    WorldSystem()
        : position(0.0f), rotation(0.0f), scale(1.0f), modelMatrix(1.0f) {
        UpdateModelMatrix();
    }

    void SetPosition(const glm::vec3& newPosition);
    glm::vec3 GetPosition() const;

    void Translate(const glm::vec3& delta);
    void Rotate(const glm::vec3& axis, float angle);
    void Rotate(const glm::vec3& newRotation);
    void Rotate(float angleX, float angleY);
    void Scale(const glm::vec3& scaleFactor);

    void Scale(const float scaleFactor);

    glm::mat4 GetModelMatrix();
    void SetCurrentShader(Shader& shader);
    glm::vec3 GetRotation() const { return rotation; }
    void SetRotation(const glm::vec3& newRotation) {
        rotation = newRotation;
        UpdateModelMatrix();
    }
    void UpdateModelMatrix();

private:


    Shader currentShader;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 lastRotation;
    glm::vec3 scale;
    glm::mat4 modelMatrix;
};
