#include "Player.h"

Player::Player(Camera& userCamera)
	: playerShader("res/shaders/playerShader.vert", "res/shaders/playerShader.frag"), playerModel("res/models/male.obj")
{
	// Set the camera we use for our Player.
	SetPlayerCamera(userCamera);
	// Create the view matrix for this player.
	//InitialisePlayerShader();
	// Initialise the model matrix

	InitialiseModelMatrix();

}

void Player::Update(float deltaTime)
{
	HandleInput(deltaTime);

	// Update player position
	glm::vec3 newPosition = playerPosition;

	// Update camera position to follow the player
	glm::vec3 cameraOffset = glm::vec3(0.0f, 0.0f, 5.0f); // Position behind and above the player
	playerCamera.Position = newPosition + cameraOffset;

	// Update the view matrix for the player
	playerShader.use();
	playerShader.setMat4("view", playerCamera.GetViewMatrix());
}

void Player::Draw()
{
	playerShader.use();
	playerModel.Draw(playerShader);
}

void Player::SetPlayerCamera(Camera& userCamera)
{
	playerCamera = userCamera;
}


void Player::InitialisePlayerShader()
{
	playerShader = Shader("res/shaders/playerShader.vert", "res/shaders/playerShader.frag");

	playerShader.use();

	glm::mat4 projection = glm::perspective(glm::radians(playerCamera.Zoom), (float)800 / (float)600 , 0.1f, 100.0f);
	playerShader.setMat4("view", playerViewMatrix);
	playerShader.setMat4("projection", projection);

}

void Player::InitialiseModelMatrix() 
{
	glm::mat4 correctionMatrix = glm::mat4(1.0f);
	correctionMatrix = glm::scale(correctionMatrix, glm::vec3(0.7f, 0.7f, 0.7f)); 
	correctionMatrix = glm::rotate(correctionMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));

	playerModelMatrix = glm::translate(correctionMatrix, playerPosition); 
	playerShader.use();
	playerShader.setMat4("model", playerModelMatrix);
}

glm::mat4 Player::GetViewMatrix()
{
	glm::vec3 cameraDirection = glm::normalize(playerCamera.Position - playerPosition);
	glm::vec3 cameraRight = glm::normalize(glm::cross(playerCamera.Up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	// Return the view matrix for the camera
	return glm::lookAt(playerCamera.Position, playerPosition, cameraUp);
}

void Player::HandleInput(float deltaTime)
{
	float velocity = 0.001f;

	if (InputManager::IsKeyPressed(GLFW_KEY_W))
	{
		playerPosition += playerCamera.Front * velocity;
	}
	if (InputManager::IsKeyPressed(GLFW_KEY_S))
	{
		playerPosition -= playerCamera.Front * velocity;
	}
	if (InputManager::IsKeyPressed(GLFW_KEY_A))
	{
		playerPosition -= glm::normalize(glm::cross(playerCamera.Front, playerCamera.Up)) * velocity;
	}
	if (InputManager::IsKeyPressed(GLFW_KEY_D))
	{
		playerPosition += glm::normalize(glm::cross(playerCamera.Front, playerCamera.Up)) * velocity;
	}

	playerModelMatrix = glm::translate(glm::mat4(1.0f), playerPosition);

}


