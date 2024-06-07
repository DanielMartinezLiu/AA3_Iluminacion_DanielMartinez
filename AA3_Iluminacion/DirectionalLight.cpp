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
	glUniform3f(glGetUniformLocation(program, "directionalLight.color"), color.x, color.y, color.z);
	glUniform1f(glGetUniformLocation(program, "directionalLight.ambientIntensity"), ambientIntensity);

	glUniform3f(glGetUniformLocation(program, "directionalLight.direction"), direction.x, direction.y, direction.z);
	glUniform1f(glGetUniformLocation(program, "directionalLight.diffuseIntensity"), diffuseIntensity);

}

DirectionalLight::~DirectionalLight()
{
}
