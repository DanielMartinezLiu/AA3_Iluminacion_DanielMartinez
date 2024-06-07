#pragma once

#include <GLFW/glfw3.h>

#define TIME_MANAGER TimeManager::Instance()

class TimeManager
{
public:
	inline static TimeManager& Instance()
	{
		static TimeManager manager;
		return manager;
	}

	TimeManager();
	void Update();
	float GetDeltaTime();

private:
	float deltaTime;
	double lastFrame;
};

