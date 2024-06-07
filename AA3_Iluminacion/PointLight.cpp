#include "PointLight.h"

PointLight::PointLight()
{
	transform.position = glm::vec3(0.f, 0.f, 0.f);
	constant = 1.f;
	linear = 0.f;
	exponent = 0.f;
}

PointLight::PointLight(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity, GLfloat _xPos, GLfloat _yPos, GLfloat _zPos, GLfloat _constant, GLfloat _linear, GLfloat _exponent)
: Light(_red, _green, _blue, _ambientIntensity, _diffuseIntensity) {
	transform.position = glm::vec3(_xPos, _yPos, _zPos);
	constant = _constant;
	linear = _linear;
	exponent = _exponent;
}

void PointLight::UsePointLight(GLuint program, int index)
{
	char uniformName[128];

	snprintf(uniformName, sizeof(uniformName), "pointLights[%d].base.color", index);
	glUniform3f(glGetUniformLocation(program, uniformName), color.x, color.y, color.z);

	snprintf(uniformName, sizeof(uniformName), "pointLights[%d].base.ambientIntensity", index);
	glUniform1f(glGetUniformLocation(program, uniformName), ambientIntensity);

	snprintf(uniformName, sizeof(uniformName), "pointLights[%d].base.diffuseIntensity", index);
	glUniform1f(glGetUniformLocation(program, uniformName), diffuseIntensity);

	snprintf(uniformName, sizeof(uniformName), "pointLights[%d].position", index);
	glUniform3f(glGetUniformLocation(program, uniformName), transform.position.x, transform.position.y, transform.position.z);

	snprintf(uniformName, sizeof(uniformName), "pointLights[%d].constant", index);
	glUniform1f(glGetUniformLocation(program, uniformName), constant);

	snprintf(uniformName, sizeof(uniformName), "pointLights[%d].linear", index);
	glUniform1f(glGetUniformLocation(program, uniformName), linear);

	snprintf(uniformName, sizeof(uniformName), "pointLights[%d].exponent", index);
	glUniform1f(glGetUniformLocation(program, uniformName), exponent);
}

PointLight::~PointLight()
{
}

void PointLight::Update()
{
}

void PointLight::Render()
{
}
