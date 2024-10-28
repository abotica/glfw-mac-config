#pragma once
#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

class Window
{
public:
	Window(const std::string& windowName, const unsigned int& scr_width, const unsigned int& scr_height);
	~Window();

	void CallBack() const;
	void SwapAndPoll() const;
	void CloseWindow() const;
	void ProcessInput() const;

	inline int isClosed() const { return glfwWindowShouldClose(m_Window); }

private:
	GLFWwindow* m_Window;
};