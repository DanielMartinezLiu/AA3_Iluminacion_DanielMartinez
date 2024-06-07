#pragma once
#include <GL/glew.h>

#include "Transform.h" 

class Entity 
{
public:
	Transform transform;

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	GLuint program;
};

