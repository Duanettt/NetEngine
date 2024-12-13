#pragma once


#include "../Renderer/Model.h"
#include "../Renderer/Camera.h"

#include "../Input/InputManager.h"


class Player
{
public:
	Player(Camera& userCamera);

	void Update(float deltaTime);

	void Draw();

	void SetPlayerCamera(Camera& userCamera);


	void InitialisePlayerShader();

	void InitialiseModelMatrix();

	glm::mat4 GetViewMatrix();

	void HandleInput(float deltaTime);

private:
	Model playerModel;
	Shader playerShader;
	Camera playerCamera;
	GLFWwindow* currentWindow;

	// player transform which is the model matrix

	glm::mat4 playerModelMatrix = glm::mat4(1.0f);
	glm::mat4 playerViewMatrix;
	glm::vec3 playerPosition = glm::vec3(0.0f);
};

