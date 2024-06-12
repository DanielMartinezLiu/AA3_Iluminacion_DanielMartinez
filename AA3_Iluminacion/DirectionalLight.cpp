#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.f, -1.f, 0.f);
}

DirectionalLight::DirectionalLight(
	GLfloat _red, GLfloat _green, GLfloat _blue,
	GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
	GLfloat _xDirection, GLfloat _yDirection, GLfloat _zDirection
) : Light(_red, _green, _blue, _ambientIntensity, _diffuseIntensity)
{
	direction = glm::vec3(_xDirection, _yDirection, _zDirection);
}

void DirectionalLight::UseDirectionalLight(GLuint program)
{
	// Configura el color base de la luz direccional
	glUniform3f(glGetUniformLocation(program, "directionalColor"), color.x, color.y, color.z);

	// Configura la intensidad ambiental de la luz direccional
	glUniform1f(glGetUniformLocation(program, "directionalAmbientIntensity"), ambientIntensity);

	// Configura la intensidad difusa de la luz direccional
	glUniform1f(glGetUniformLocation(program, "directionalDiffuseIntensity"), diffuseIntensity);

	// Configura la dirección de la luz direccional
	glUniform3f(glGetUniformLocation(program, "directionalDirection"), direction.x, direction.y, direction.z);
}

DirectionalLight::~DirectionalLight()
{
}
