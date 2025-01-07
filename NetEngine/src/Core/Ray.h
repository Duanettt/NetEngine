#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "../Renderer/Camera.h"

class Ray
{
public:
	Ray() = default;

	void SetProjectionMatrix(glm::mat4& projectionMatrix);

	glm::mat4& GetProjectionMatrix();

	glm::vec3 ScreenToWorldRay(const glm::vec2& mousePos, int screenWidth, int screenHeight, Camera& camera);
private:
	glm::mat4 m_projectionMatrix;

};

