#include "TimeManager.h"

TimeManager::TimeManager() : 
	deltaTime(0.0f), 
	lastFrame(0.0f) {}

void TimeManager::Update()
{
	double currentFrame = glfwGetTime();
	deltaTime = static_cast<float>(currentFrame - lastFrame);
	lastFrame = currentFrame;
}

float TimeManager::GetDeltaTime()
{
	return deltaTime;
}
