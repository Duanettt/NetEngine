#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Renderer/Camera.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow* window);

unsigned int loadTexture(const char* path);

struct Cursor
{
	bool firstMouse = true;
	float x, y;
	float lastX = 800.0 / 2.0;
	float lastY = 600.0 / 2.0;

	void Update(double xposIn, double yposIn, Camera& camera)
	{
		//std::cout << "Heres our mouse xposIn: " << xposIn << " Heres our mouse yPosIn: " << yposIn << std::endl;
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (this->firstMouse)
		{
			this->lastX = xposIn;
			this->lastY = yposIn;
			this->firstMouse = false;
		}

		float xoffset = xpos - this->lastX;
		float yoffset = this->lastY - ypos;

		x = xpos;
		y = ypos;


		this->lastX = xpos;
		this->lastY = ypos;


		camera.ProcessMouseMovement(xoffset, yoffset);

	};

	inline glm::vec2 GetScreenPosition()
	{
		return glm::vec2(lastX, lastY);
	}

};



class Window
{

public:
	Window(int screenWidth, int screenHeight, const char* windowName);
	int CreateWindow();
	void SetCurrentContext();
	void SetCallbacks(void(*mouse_callback)(GLFWwindow* window, double xpos, double ypos));
 
	void SetInputMode();

	glm::vec2 GetCursorPosition();
	
	Cursor* cursor;

	GLFWwindow* GetWindow();

	void SetWindowUserPointer(void* pointer);

private:

	GLFWwindow* currentWindow;

	int windowScreenWidth;

	int windowScreenHeight;

};
