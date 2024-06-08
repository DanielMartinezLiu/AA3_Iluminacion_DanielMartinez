#include "TimeManager.h"

TimeManager::TimeManager() : 
	deltaTime(0.0f), 
	lastFrame(0.0f) {}

void TimeManager::Update()
{
	// Obtener el tiempo actual en segundos desde que GLFW se inicializó
	double currentFrame = glfwGetTime();

	// Calcular el tiempo transcurrido desde el último fotograma (deltaTime)
	deltaTime = static_cast<float>(currentFrame - lastFrame);

	// Actualizar el tiempo del último fotograma al tiempo actual
	lastFrame = currentFrame;
}

float TimeManager::GetDeltaTime()
{
	return deltaTime;
}
