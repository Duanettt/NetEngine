#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../Renderer/Mesh.h"


class Cube
{
public:

	Cube() = default;
	Cube(unsigned int texture);

	void uploadVertexData();

	void Draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);


	void move(float deltaTime);

	glm::vec3 GetPosition();

	float GetPositionX();

	float GetPositionY();

	float GetPositionZ();

	void SetPosition(glm::vec3 newPosition);

	void SetShader(Shader& cubeShader);

	void HandleInput(GLFWwindow* window, float deltaTime);

	void updateModelMatrix();

private:

	Shader cubeShader;
	unsigned int VAO, VBO, cubeTexture;
	std::vector<Vertex> vertices;
	glm::vec3 position;
	glm::mat4 cubeModelMatrix;

	float currentSpeed;
};
