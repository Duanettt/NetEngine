#include "DebugRenderer.h"

// DebugLineRenderer implementation
DebugLineRenderer::DebugLineRenderer(const glm::vec3 origin, const glm::vec3 end)
{
    debugVertices.push_back({ origin });
    debugVertices.push_back({ end });

    debugMesh = std::make_unique<Mesh>(debugVertices);
    debugMesh->setupMesh();
}

void DebugLineRenderer::Draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::mat4& model)
{
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setMat4("model", model);

    debugMesh->Draw(GL_LINES);
}

// DefaultDebugRendererFactory implementation
std::unique_ptr<DebugRenderer> DefaultDebugRendererFactory::CreateDebugLineRenderer(const glm::vec3 origin, const glm::vec3 end)
{
    return std::make_unique<DebugLineRenderer>(origin, end);
}
