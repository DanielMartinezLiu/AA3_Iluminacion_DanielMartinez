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
	// Obtener el puntero al objeto GLManager asociado a la ventana de GLFW
	GLManager* mouseWindow = static_cast<GLManager*>(glfwGetWindowUserPointer(window));

	// Verificar si es el primer movimiento del ratón
	if (mouseWindow->mouseFirstMoved)
	{
		// Si es el primer movimiento, establecer las coordenadas del último movimiento como las actuales
		mouseWindow->lastX = (GLfloat)xPos;
		mouseWindow->lastY = (GLfloat)yPos;
		mouseWindow->mouseFirstMoved = false;
	}

	// Calcular el cambio en las coordenadas del ratón desde el último fotograma
	mouseWindow->xChange = (GLfloat)xPos - mouseWindow->lastX;
	mouseWindow->yChange = mouseWindow->lastY - (GLfloat)yPos;

	// Actualizar las coordenadas del último movimiento del ratón
	mouseWindow->lastX = (GLfloat)xPos;
	mouseWindow->lastY = (GLfloat)yPos;
}

void GLManager::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	// Obtener el puntero al objeto GLManager asociado a la ventana GLFW
	GLManager* keyWindow = static_cast<GLManager*>(glfwGetWindowUserPointer(window));

	// Verificar si se presionó la tecla Escape y si es así, cerrar la ventana
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// Verificar si la tecla presionada está dentro del rango de teclas válidas (0 a 1023)
	if (key >= 0 && key < 1024)
	{
		// Si la acción es presionar, se marca la tecla como presionada
		if (action == GLFW_PRESS)
		{
			keyWindow->keys[key] = true;
		}
		// Si la acción es liberar, se marca la tecla como no presionada
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

