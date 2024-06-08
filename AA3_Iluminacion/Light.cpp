#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.f, 1.f, 1.f);
	ambientIntensity = 1.f;

	diffuseIntensity = 0.f;
}

Light::Light(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity,
	GLfloat _diffuseIntensity)
{
	color = glm::vec3(_red, _green, _blue);
	ambientIntensity = _ambientIntensity;

	diffuseIntensity = _diffuseIntensity;
}

Light::~Light()
{
}
