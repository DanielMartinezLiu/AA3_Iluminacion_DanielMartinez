#pragma once
#include "Transform.h" 
#include "Light.h"
class Entity 
{
public:
	Transform transform;

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	GLuint program;
	Light light;
};

