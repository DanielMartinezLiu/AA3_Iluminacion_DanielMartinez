#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include "ProgramManager.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define GLM GLManager::Instance()

class GLManager
{
private:
	enum DrawMode
	{
		FILL,
		LINE
	};

	GLFWwindow* window;
	DrawMode drawMode;

	GLManager();

	GLManager(const GLManager&) = delete;
	GLManager& operator =(const GLManager&) = delete;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void CreateCallbacks();
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);

public:
	inline static GLManager& Instance()
	{
		static GLManager manager;
		return manager;
	}

	void Init();

	void ClearColor();
	void ClearBuffers();
	void ChangeBuffers();

	void SwapDrawMode();

	bool* GetsKeys() { return keys; }

	GLfloat GetXChange();
	GLfloat GetYChange();

	inline GLFWwindow* GetWindow() { return window; }
	inline bool IsRunnig() { return !glfwWindowShouldClose(window); }


};

