#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
	ambientIntensityOriginal = 1.f;

	direction = glm::vec3(0.f, 0.f, 0.f);
	cutOff = 0.f;
	outerCutOff = 0.f;

	lightActive = false;
	isPressing = false;
}

SpotLight::SpotLight(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity, GLfloat _xPos, GLfloat _yPos, GLfloat _zPos, GLfloat _xDir, GLfloat _yDir, GLfloat _zDir, GLfloat _constant, GLfloat _linear, GLfloat _quadratic, GLfloat _cutOff, GLfloat _outerCutOff)
	: PointLight(_red, _green, _blue, _ambientIntensity, _xPos, _yPos, _zPos, _constant, _linear, _quadratic)
{
	ambientIntensityOriginal = _ambientIntensity;

	direction = glm::vec3(_xDir, _yDir, _zDir);

	cutOff = _cutOff;
	outerCutOff = _outerCutOff;

	lightActive = false;
	isPressing = false;
}

void SpotLight::UseSpotLight(GLuint program)
{
	char uniformName[128];

	// Configura el color base de la foco de luz
	glUniform3f(glGetUniformLocation(program, "spotColor"), color.x, color.y, color.z);

	// Configura la intensidad ambiental de el foco de luz
	glUniform1f(glGetUniformLocation(program, "spotAmbientIntensity"), ambientIntensity);

	// Configura la posición de el foco de luz
	glUniform3f(glGetUniformLocation(program, "spotPosition"), transform.position.x, transform.position.y, transform.position.z);

	// Configura el factor de atenuación constante de el foco de luz
	glUniform1f(glGetUniformLocation(program, "spotConstant"), constant);

	// Configura el factor de atenuación lineal de el foco de luz
	glUniform1f(glGetUniformLocation(program, "spotLinear"), linear);

	// Configura el factor de atenuación exponencial de el foco de luz
	glUniform1f(glGetUniformLocation(program, "spotQuadratic"), quadratic);

	// Configura la direccion de el foco de luz
	glUniform3f(glGetUniformLocation(program, "spotDirection"), direction.x, direction.y, direction.z);

	// Configura el angulo interior del foco de luz
	glUniform1f(glGetUniformLocation(program, "spotCutOff"), cutOff);

	// Configura el angulo exterior del foco de luz
	glUniform1f(glGetUniformLocation(program, "spotOuterCutOff"), outerCutOff);
}

void SpotLight::SetCamera(Camera* _camera)
{
	camera = _camera;
}

void SpotLight::Update()
{
	// Llama a la funcion KeyControl y pasa las teclas presionadas
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
