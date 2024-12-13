#pragma once
#include <GLFW/glfw3.h>

class InputManager 
{
public:
    static void Initialize(GLFWwindow* window);
    static bool IsKeyPressed(int key);
    static bool IsMouseButtonPressed(int button);
    static void GetMousePosition(float& x, float& y);

private:
    static GLFWwindow* s_Window;
};

