#include "Window.h"

Window::Window(int screenWidth, int screenHeight, const char* windowName) : windowScreenHeight(screenHeight), windowScreenWidth(screenWidth)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}



int Window::CreateWindow()
{
    currentWindow = glfwCreateWindow(windowScreenWidth, windowScreenHeight, "LearnOpenGL", NULL, NULL);
    if (currentWindow == NULL)
    {

        std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();

        return -1;

    }

}



void Window::SetCurrentContext()
{

    glfwMakeContextCurrent(this->GetWindow());

}

void Window::SetCallbacks(void(*mouse_callback)(GLFWwindow* window, double xpos, double ypos))
{
    glfwSetFramebufferSizeCallback(this->GetWindow(), framebuffer_size_callback);

    glfwSetCursorPosCallback(this->GetWindow(), mouse_callback);

    //glfwSetScrollCallback(this->GetWindow(), scroll_callback);
}



void Window::SetInputMode()
{
    glfwSetInputMode(this->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

glm::vec2 Window::GetCursorPosition()
{
    double xpos, ypos;
    glfwGetCursorPos(this->currentWindow, &xpos, &ypos);
    return glm::vec2(xpos, ypos);
}


GLFWwindow* Window::GetWindow()
{

    return currentWindow;

}

void Window::SetWindowUserPointer(void* pointer)
{
    glfwSetWindowUserPointer(this->GetWindow(), pointer);
}





void framebuffer_size_callback(GLFWwindow* window, int width, int height)

{

    // make sure the viewport matches the new window dimensions; note that width and 

    // height will be significantly larger than specified on retina displays.

    glViewport(0, 0, width, height);

}



// glfw: whenever the mouse moves, this callback is called

// -------------------------------------------------------

