#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
	ambientIntensityOriginal = 1.f;

	direction = glm::vec3(0.f, 0.f, 0.f);
	edge = 0.f;

	lightActive = false;
	isPressing = false;
}

SpotLight::SpotLight(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity, GLfloat _xPos, GLfloat _yPos, GLfloat _zPos, GLfloat _xDir, GLfloat _yDir, GLfloat _zDir, GLfloat _constant, GLfloat _linear, GLfloat _exponent, GLfloat _edge)
	: PointLight(_red, _green, _blue, _ambientIntensity, _diffuseIntensity, _xPos, _yPos, _zPos, _constant, _linear, _exponent)
{
	ambientIntensityOriginal = _ambientIntensity;

	direction = glm::vec3(_xDir, _yDir, _zDir);

	edge = _edge;
	procEdge = cosf(glm::radians(edge));

	lightActive = false;
	isPressing = false;
}

void SpotLight::UseSpotLight(GLuint program, int index)
{
	char uniformName[128];

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.base.color", index);
	glUniform3f(glGetUniformLocation(program, uniformName), color.x, color.y, color.z);

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.base.ambientIntensity", index);
	glUniform1f(glGetUniformLocation(program, uniformName), ambientIntensity);

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.base.diffuseIntensity", index);
	glUniform1f(glGetUniformLocation(program, uniformName), diffuseIntensity);

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.position", index);
	glUniform3f(glGetUniformLocation(program, uniformName), transform.position.x, transform.position.y, transform.position.z);

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.constant", index);
	glUniform1f(glGetUniformLocation(program, uniformName), constant);

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.linear", index);
	glUniform1f(glGetUniformLocation(program, uniformName), linear);

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.exponent", index);
	glUniform1f(glGetUniformLocation(program, uniformName), exponent);

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].direction", index);
	glUniform3f(glGetUniformLocation(program, uniformName), direction.x, direction.y, direction.z);

	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].edge", index);
	glUniform1f(glGetUniformLocation(program, uniformName), procEdge);
}

void SpotLight::SetCamera(Camera* _camera)
{
	camera = _camera;
}

void SpotLight::Update()
{
	KeyControl(GLM.GetsKeys());

	if (lightActive)
	{
		ambientIntensity = ambientIntensityOriginal;
	}
	else
	{
		ambientIntensity = 0.f;
	}

	if (camera) {
		direction = camera->GetCameraDirection();

		transform.position = camera->GetCameraPosition();
	}
}

void SpotLight::Render()
{
}

void SpotLight::KeyControl(bool* keys)
{
	if (keys[GLFW_KEY_F] && !isPressing)
	{
		lightActive = !lightActive;
		isPressing = true;
	}
	else if (!keys[GLFW_KEY_F] && isPressing)
	{
		isPressing = false;
	}
}

SpotLight::~SpotLight()
{
}
