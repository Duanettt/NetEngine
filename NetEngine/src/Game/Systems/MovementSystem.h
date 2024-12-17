#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class MovementSystem
{
public:
	float GetRunSpeed();
	float GetTurnSpeed();
	void SetTurnSpeed(float turnSpeed);
	void SetRunSpeed(float runSpeed);
private:
	glm::vec3 movement;
	float m_runSpeed;
	float m_turnSpeed;

};

