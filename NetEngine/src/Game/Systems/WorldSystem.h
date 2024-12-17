#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Renderer/Shader.h"

class WorldSystem
{
public:
    WorldSystem()
        : position(0.0f), rotation(0.0f), scale(1.0f), modelMatrix(1.0f) {}

    void SetPosition(const glm::vec3& newPosition);
    glm::vec3 GetPosition() const;

    void Translate(const glm::vec3& delta);
    void Rotate(const glm::vec3& axis, float angle);
    void Scale(const glm::vec3& scaleFactor);

    glm::mat4 GetModelMatrix();
    void SetCurrentShader(Shader& shader);

private:
    void UpdateModelMatrix();


    Shader currentShader;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 modelMatrix;
};
