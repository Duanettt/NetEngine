#include "Ray.h"

void Ray::SetProjectionMatrix(glm::mat4& projectionMatrix)
{
	m_projectionMatrix = projectionMatrix; 
}

glm::mat4& Ray::GetProjectionMatrix()
{
	return m_projectionMatrix;
}

glm::vec3 Ray::ScreenToWorldRay(const glm::vec2& mousePos, int screenWidth, int screenHeight, Camera& camera)
{
	// Convert from screen space to normalized device coordinates
	/* So we get our Mouse position divide it by the screen width to get a range of 0,1 we then multiply it by 2 to get a range from 0,2 and then we subtract 1 to get -1,1*/
	float ndcX = (2.0 * mousePos.x) / screenWidth - 1.0f;
	float ndcY = 1.0 - (2.0 * mousePos.y) / screenHeight;

	glm::vec4 clipCoordinates(ndcX, ndcY, -1.0f, 1.0);
	glm::vec4 eyeCoords = glm::inverse(GetProjectionMatrix()) * clipCoordinates;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0);

	glm::vec3 worldRay = glm::normalize(glm::vec3(glm::inverse(camera.GetViewMatrix()) * eyeCoords));

	return worldRay;
}


