#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();

	DirectionalLight(
		GLfloat _red, GLfloat _green, GLfloat _blue, 
		GLfloat _ambientIntensity,
		GLfloat _xDirection, GLfloat _yDirection, GLfloat _zDirection
	);

	void UseDirectionalLight(GLuint program);

	~DirectionalLight();

private:
	glm::vec3 direction;
};

