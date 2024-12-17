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

void WorldSystem::Scale(const glm::vec3& scaleFactor)
{
    scale *= scaleFactor;
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

    currentShader.use();
    currentShader.setMat4("model", modelMatrix);
}

void WorldSystem::SetCurrentShader(Shader& shader)
{
    currentShader = shader;
}
