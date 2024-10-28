#include "Window.h"

#include <iostream>
#include <assert.h>

Window::Window(const std::string& name, const unsigned int& scr_width, const unsigned int& scr_height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_Window = glfwCreateWindow(scr_width, scr_height, name.c_str(), NULL, NULL);
    if (m_Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    CallBack();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        assert(true);
    }
}

Window::~Window()
{
    CloseWindow();
}

void Window::CallBack() const
{
	glfwMakeContextCurrent(m_Window);
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
}

void Window::SwapAndPoll() const
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void Window::CloseWindow() const
{
    glfwTerminate();
}

void Window::ProcessInput() const
{
    processInput(m_Window);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}