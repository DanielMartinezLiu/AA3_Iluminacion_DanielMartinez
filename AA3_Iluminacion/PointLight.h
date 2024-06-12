#pragma once
#include "Light.h"

class PointLight : public Entity, public Light
{
public: 
	PointLight();
	PointLight(
		GLfloat _red, GLfloat _green, GLfloat _blue,
		GLfloat _ambientIntensity,
		GLfloat _xPos, GLfloat _yPos, GLfloat _zPos,
		GLfloat _constant, GLfloat _linear, GLfloat _quadratic);

	PointLight(
		GLfloat _red, GLfloat _green, GLfloat _blue,
		GLfloat _ambientIntensity,
		GLfloat _xPos, GLfloat _yPos, GLfloat _zPos,
		GLfloat _constant, GLfloat _linear, GLfloat _quadratic,
		GLfloat _radius, GLfloat _speed, GLfloat _angle
	);

	void UsePointLight(GLuint program);

	~PointLight();

	void Update() override;
	void Render() override;

protected:
	GLfloat constant;
	GLfloat linear;
	GLfloat quadratic;

private:
	glm::vec3 center;

	float radius;
	float speed;
	float angle;

	float ambientIntesityOriginal;

	float deltaTime;
};

