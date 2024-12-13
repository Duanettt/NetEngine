#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow* window);

unsigned int loadTexture(const char* path);

struct Cursor
{
	bool firstMouse;
	int lastX;
	int lastY;

};



class Window
{

public:
	Window(int screenWidth, int screenHeight, const char* windowName);
	int CreateWindow();
	void SetCurrentContext();
	void SetCallbacks(void(*mouse_callback)(GLFWwindow* window, double xpos, double ypos));
 
	void SetInputMode();

	Cursor* cursor;

	GLFWwindow* GetWindow();

	void SetWindowUserPointer(void* pointer);

private:

	GLFWwindow* currentWindow;

	int windowScreenWidth;

	int windowScreenHeight;

};
