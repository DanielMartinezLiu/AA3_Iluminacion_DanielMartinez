#include "GLManager.h"

GLManager::GLManager()
{
	window = nullptr;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;
}

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight)
{
	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);

	glUniform2f(glGetUniformLocation(PROGRAMS.GetCompiledPrograms()[0], "windowSize"), iFrameBufferWidth, iFrameBufferHeight);
}

void GLManager::Init()
{
	//Definir semillas del rand según el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	//Configuramos la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AA3_Iluminacion", NULL, NULL);

	//Asignamos función de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	CreateCallbacks();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_BACK);

	glfwSetWindowUserPointer(window, this);
}

GLfloat GLManager::GetXChange()
{
	GLfloat result = xChange;
	xChange = 0.0f;
	return result;
}

GLfloat GLManager::GetYChange()
{
	GLfloat result = yChange;
	yChange = 0.0f;
	return result;
}

void GLManager::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	GLManager* mouseWindow = static_cast<GLManager*>(glfwGetWindowUserPointer(window));

	if (mouseWindow->mouseFirstMoved)
	{
		mouseWindow->lastX = xPos;
		mouseWindow->lastY = yPos;
		mouseWindow->mouseFirstMoved = false;
	}

	mouseWindow->xChange = xPos - mouseWindow->lastX;
	mouseWindow->yChange = mouseWindow->lastY - yPos;

	mouseWindow->lastX = xPos;
	mouseWindow->lastY = yPos;
}

void GLManager::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	GLManager* keyWindow = static_cast<GLManager*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keyWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keyWindow->keys[key] = false;
		}
	}
}

void GLManager::CreateCallbacks()
{
	glfwSetKeyCallback(window, HandleKeys);
	glfwSetCursorPosCallback(window, HandleMouse);
}

void GLManager::ClearColor()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void GLManager::ClearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GLManager::ChangeBuffers()
{
	glFlush();
	glfwSwapBuffers(window);
}

void GLManager::SwapDrawMode()
{
	drawMode = (DrawMode)(((int)drawMode + 1) % 2);

	if (drawMode == FILL)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

