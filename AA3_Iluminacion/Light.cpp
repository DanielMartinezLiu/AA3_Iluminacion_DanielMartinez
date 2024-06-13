#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.f, 1.f, 1.f);
	ambientIntensity = 1.f;
}

Light::Light(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity)
{
	color = glm::vec3(_red, _green, _blue);
	ambientIntensity = _ambientIntensity;
}

Light::~Light()
{
}
