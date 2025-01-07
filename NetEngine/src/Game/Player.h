#pragma once
#include <memory>
#include "Transform.h"
#include "../Renderer/Model.h"
#include "Systems/WorldSystem.h"

class Player {
public:
    Player() :
        playerShader("res/shaders/playerShader.vert", "res/shaders/playerShader.frag"),
        playerMatrixTransformation(glm::mat4(1.0f)),
        playerPosition(glm::vec3(1.0f)),
        isInitialized(false)
    {
        Initialize();
    }

    void Initialize() {
        try {
            playerModel = std::make_unique<Model>("res/models/male.obj");
            if (!playerModel) {
                throw std::runtime_error("Failed to create player model");
            }

            // Verify shader compilation
            isInitialized = true;
        }
        catch (const std::exception& e) {
            std::cerr << "Player initialization failed: " << e.what() << std::endl;
            isInitialized = false;
        }
    }

    void Update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
        if (!isInitialized) {
            std::cerr << "Cannot update uninitialized player" << std::endl;
            return;
        }

        playerShader.use();
        playerShader.setMat4("view", viewMatrix);
        playerShader.setMat4("projection", projectionMatrix);
        playerShader.setMat4("model", playerMatrixTransformation);
    }

    void Draw() {
        if (!isInitialized) {
            std::cerr << "Cannot draw uninitialized player" << std::endl;
            return;
        }

        if (!playerModel) {
            std::cerr << "Player model is null" << std::endl;
            return;
        }

        playerShader.use();
        playerModel->Draw(playerShader);
    }

private:
    std::unique_ptr<Model> playerModel;
    Shader playerShader;
    glm::mat4 playerMatrixTransformation;
    glm::vec3 playerPosition;
    bool isInitialized;
};