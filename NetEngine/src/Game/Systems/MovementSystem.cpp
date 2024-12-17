#include "MovementSystem.h"

float MovementSystem::GetRunSpeed()
{
	return m_runSpeed;
}

float MovementSystem::GetTurnSpeed()
{
	return m_turnSpeed;
}

void MovementSystem::SetTurnSpeed(float turnSpeed)
{
	m_turnSpeed = turnSpeed;
}

void MovementSystem::SetRunSpeed(float runSpeed)
{
	m_runSpeed = runSpeed;
}
