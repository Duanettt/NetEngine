#include "InputManager.h"

GLFWwindow* InputManager::s_Window = nullptr;

void InputManager::Initialize(GLFWwindow* window)
{
	s_Window = window;
}

bool InputManager::IsKeyPressed(int key)
{
	return glfwGetKey(s_Window, key) == GLFW_PRESS;
}

bool InputManager::IsMouseButtonPressed(int button)
{
	return glfwGetMouseButton(s_Window, button) == GLFW_PRESS;
}

void InputManager::GetMousePosition(float& x, float& y)
{
	double xpos;
	double ypos;

	glfwGetCursorPos(s_Window, &xpos, &ypos);
	xpos = static_cast<float>(xpos);
	ypos = static_cast<float>(ypos);

}
