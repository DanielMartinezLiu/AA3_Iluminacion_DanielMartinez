#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.f, 1.f, 1.f);
	ambientIntensity = 1.f;

	direction = glm::vec3(0.f, -1.f, 0.f);
	diffuseIntensity = 0.f;
}

Light::Light(GLfloat _eyePositionX, GLfloat _eyePositionY, GLfloat _eyePositionZ, 
	GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity,
	GLfloat _xDirection, GLfloat _yDirection, GLfloat _zDirection, GLfloat _diffuseIntensity,
	Material _material)
{
	eyePosition = glm::vec3(_eyePositionX, _eyePositionY, _eyePositionZ);

	color = glm::vec3(_red, _green, _blue);
	ambientIntensity = _ambientIntensity;

	direction = glm::vec3(_xDirection, _yDirection, _zDirection);
	diffuseIntensity = _diffuseIntensity;

	material = _material;
}

void Light::UseLight(GLuint program)
{
	glUniform3f(glGetUniformLocation(program, "eyePosition"), eyePosition.x, eyePosition.y, eyePosition.z);

	glUniform3f(glGetUniformLocation(program, "directionalLight.color"), color.x, color.y, color.z);
	glUniform1f(glGetUniformLocation(program, "directionalLight.ambientIntensity"), ambientIntensity);

	glUniform3f(glGetUniformLocation(program, "directionalLight.direction"), direction.x, direction.y, direction.z);
	glUniform1f(glGetUniformLocation(program, "directionalLight.diffuseIntensity"), diffuseIntensity);

	material.UseMaterial(program);
}

Light::~Light()
{
}
