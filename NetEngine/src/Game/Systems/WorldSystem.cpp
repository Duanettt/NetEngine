#include "WorldSystem.h"
#include "../../Renderer/Shader.h"

void WorldSystem::SetPosition(const glm::vec3& newPosition)
{
    position = newPosition;
    UpdateModelMatrix();
}

glm::vec3 WorldSystem::GetPosition() const
{
    return position;
}

void WorldSystem::Translate(const glm::vec3& delta)
{
    position += delta;
    UpdateModelMatrix();
}

void WorldSystem::Rotate(const glm::vec3& axis, float angle)
{
    rotation += axis * angle; // Store rotation
    UpdateModelMatrix();
}

void WorldSystem::Rotate(const glm::vec3& newRotation)
{
    rotation = newRotation; // Store rotation
    UpdateModelMatrix();
}

void WorldSystem::Rotate(float angleX, float angleY)
{
    rotation += glm::vec3(1, 0, 0) * angleX;
    rotation += glm::vec3(0, 1, 0) * angleY;
}

void WorldSystem::Scale(const glm::vec3& scaleFactor)
{
    scale *= scaleFactor;
    UpdateModelMatrix();
}

void WorldSystem::Scale(const float scaleFactor)
{
    scale *= glm::vec3(scaleFactor, scaleFactor, scaleFactor);
    UpdateModelMatrix();
}

glm::mat4 WorldSystem::GetModelMatrix()
{
    return modelMatrix;
}

void WorldSystem::UpdateModelMatrix()
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, scale);
    // Applies our rotation.

    //modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
    //modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));

    

    currentShader.use();
    currentShader.setMat4("model", modelMatrix);
}

void WorldSystem::SetCurrentShader(Shader& shader)
{
    currentShader = shader;
}


