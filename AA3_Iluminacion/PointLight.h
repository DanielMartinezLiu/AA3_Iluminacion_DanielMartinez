#pragma once
#include "Light.h"

class PointLight : public Entity, public Light
{
public: 
	PointLight();
	PointLight(
		GLfloat _red, GLfloat _green, GLfloat _blue,
		GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
		GLfloat _xPos, GLfloat _yPos, GLfloat _zPos,
		GLfloat _constant, GLfloat _linear, GLfloat _exponent);

	void UsePointLight(GLuint program, int index);

	~PointLight();

	void Update() override;
	void Render() override;

protected:
	GLfloat constant;
	GLfloat linear;
	GLfloat exponent;
};

