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

void DirectionalLight::UseDirectionalLight(GLuint program, int index)
{
	// Crea un nombre de uniforme dinámico basado en el índice 'index' de la luz direccional
	char uniformName[128];

	// Configura el color base de la luz direccional
	snprintf(uniformName, sizeof(uniformName), "directionalLights[%d].base.color", index);
	glUniform3f(glGetUniformLocation(program, uniformName), color.x, color.y, color.z);

	// Configura la intensidad ambiental de la luz direccional
	snprintf(uniformName, sizeof(uniformName), "directionalLights[%d].base.ambientIntensity", index);
	glUniform1f(glGetUniformLocation(program, uniformName), ambientIntensity);

	// Configura la intensidad difusa de la luz direccional
	snprintf(uniformName, sizeof(uniformName), "directionalLights[%d].base.diffuseIntensity", index);
	glUniform1f(glGetUniformLocation(program, uniformName), diffuseIntensity);

	// Configura la dirección de la luz direccional
	snprintf(uniformName, sizeof(uniformName), "directionalLights[%d].direction", index);
	glUniform3f(glGetUniformLocation(program, uniformName), direction.x, direction.y, direction.z);
}

DirectionalLight::~DirectionalLight()
{
}
