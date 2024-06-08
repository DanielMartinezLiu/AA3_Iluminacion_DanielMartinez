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

	// Configura el color base de la foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.base.color", index);
	glUniform3f(glGetUniformLocation(program, uniformName), color.x, color.y, color.z);

	// Configura la intensidad ambiental de el foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.base.ambientIntensity", index);
	glUniform1f(glGetUniformLocation(program, uniformName), ambientIntensity);

	// Configura la intensidad difusa de el foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.base.diffuseIntensity", index);
	glUniform1f(glGetUniformLocation(program, uniformName), diffuseIntensity);

	// Configura la posición de el foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.position", index);
	glUniform3f(glGetUniformLocation(program, uniformName), transform.position.x, transform.position.y, transform.position.z);

	// Configura el factor de atenuación constante de el foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.constant", index);
	glUniform1f(glGetUniformLocation(program, uniformName), constant);

	// Configura el factor de atenuación lineal de el foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.linear", index);
	glUniform1f(glGetUniformLocation(program, uniformName), linear);

	// Configura el factor de atenuación exponencial de el foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].pointBase.exponent", index);
	glUniform1f(glGetUniformLocation(program, uniformName), exponent);

	// Configura la direccion de el foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].direction", index);
	glUniform3f(glGetUniformLocation(program, uniformName), direction.x, direction.y, direction.z);

	// Configura el angulo del foco de luz
	snprintf(uniformName, sizeof(uniformName), "spotLights[%d].edge", index);
	glUniform1f(glGetUniformLocation(program, uniformName), procEdge);
}

void SpotLight::SetCamera(Camera* _camera)
{
	camera = _camera;
}

void SpotLight::Update()
{
	// Llama a la función KeyControl y pasa las teclas presionadas
	KeyControl(GLM.GetsKeys());

	if (lightActive)
	{
		// Si la luz está activa, establece la intensidad ambiental a su valor original
		ambientIntensity = ambientIntensityOriginal;
	}
	else
	{
		// Si la luz no está activa, establece la intensidad ambiental a 0
		ambientIntensity = 0.f;
	}

	if (camera) {
		// Obtiene la dirección de la cámara
		direction = camera->GetCameraDirection();

		// Actualiza la posición del transform a la posición de la cámara
		transform.position = camera->GetCameraPosition();
	}
}

void SpotLight::Render()
{
}

void SpotLight::KeyControl(bool* keys)
{
	// Verifica si la tecla 'F' está presionada y si no se está en un estado de "presionando"
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
