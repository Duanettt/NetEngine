#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "../Mesh.h"
#include "../Shader.h"

// Abstract base class for all debug renderers
class DebugRenderer
{
public:
    virtual ~DebugRenderer() = default;

    virtual void Draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::mat4& model) = 0;

protected:
    std::unique_ptr<Mesh> debugMesh;
    std::vector<Vertex> debugVertices;
};

// DebugLineRenderer implementation
class DebugLineRenderer : public DebugRenderer
{
public:
    DebugLineRenderer(const glm::vec3 origin, const glm::vec3 end);
    void Draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::mat4& model) override;
};

// Abstract factory interface
class DebugRendererFactory
{
public:
    virtual ~DebugRendererFactory() = default;
    virtual std::unique_ptr<DebugRenderer> CreateDebugLineRenderer(const glm::vec3 origin, const glm::vec3 end) = 0;
};

// Might remove this i feel like its unnecessary we'll see.
class DefaultDebugRendererFactory : public DebugRendererFactory
{
public:
    std::unique_ptr<DebugRenderer> CreateDebugLineRenderer(const glm::vec3 origin, const glm::vec3 end) override;
};
