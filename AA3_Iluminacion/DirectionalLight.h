#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();

	DirectionalLight(
		GLfloat _red, GLfloat _green, GLfloat _blue, 
		GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
		GLfloat _xDirection, GLfloat _yDirection, GLfloat _zDirection
	);

	void UseDirectionalLight(GLuint program, int index);

	~DirectionalLight();

private:
	glm::vec3 direction;
};

