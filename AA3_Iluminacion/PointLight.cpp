#include "PointLight.h"

PointLight::PointLight() : Light()
{
	transform.position = glm::vec3(0.f, 0.f, 0.f);

	constant = 1.f;
	linear = 0.f;
	exponent = 0.f;

	center = glm::vec3(0.f);
	radius = 7.5f;
	speed = glm::two_pi<float>() / 20.f;
	angle = 0.f;
}

PointLight::PointLight(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity, GLfloat _xPos, GLfloat _yPos, GLfloat _zPos, GLfloat _constant, GLfloat _linear, GLfloat _exponent)
: Light(_red, _green, _blue, _ambientIntensity, _diffuseIntensity) {
	transform.position = glm::vec3(_xPos, _yPos, _zPos);

	ambientIntesityOriginal = _ambientIntensity;
	diffuseIntesityOriginal = _diffuseIntensity;

	constant = _constant;
	linear = _linear;
	exponent = _exponent;

	center = glm::vec3(0.f, -1.f, 0.f);
	radius = 7.5f;
	speed = glm::two_pi<float>() / 20.f;
	angle = 0.f;
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
	angle += speed * TIME_MANAGER.GetDeltaTime();

	if (angle > glm::two_pi<float>()) {
		angle -= glm::two_pi<float>();
	}

	transform.position.x = center.x + radius * cos(angle);
	transform.position.y = center.y + radius * sin(angle);
	transform.position.z = 0;

	float blendFactor = (transform.position.y - center.y + radius) / (2.0f * radius);

	glm::vec3 sunColor(1.0f, 1.0f, 0.0f);
	glm::vec3 moonColor(0.0f, 0.0f, 1.0f);

	color = glm::mix(moonColor, sunColor, blendFactor);

	float intensityFactor = glm::mix(0.85f, 1.0f, blendFactor);
	ambientIntensity = ambientIntesityOriginal * intensityFactor;
	diffuseIntensity = diffuseIntesityOriginal * intensityFactor;
}

void PointLight::Render()
{
}
