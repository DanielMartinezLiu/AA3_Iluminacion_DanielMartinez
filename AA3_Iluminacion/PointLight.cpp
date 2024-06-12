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

	center = glm::vec3(0.f);
	radius = 7.5f;
	speed = glm::two_pi<float>() / 20.f;
	angle = 0.f;
}

PointLight::PointLight(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity, GLfloat _xPos, GLfloat _yPos, GLfloat _zPos, GLfloat _constant, GLfloat _linear, GLfloat _exponent, GLfloat _radius, GLfloat _speed, GLfloat _angle)
	: Light(_red, _green, _blue, _ambientIntensity, _diffuseIntensity) {
	transform.position = glm::vec3(_xPos, _yPos, _zPos);

	ambientIntesityOriginal = _ambientIntensity;
	diffuseIntesityOriginal = _diffuseIntensity;

	constant = _constant;
	linear = _linear;
	exponent = _exponent;

	center = glm::vec3(0.f);
	radius = _radius;
	speed = _speed;
	angle = _angle;
}

void PointLight::UsePointLight(GLuint program)
{
	// Configura el color base de la point light
	glUniform3f(glGetUniformLocation(program, "pointColor"), color.x, color.y, color.z);

	// Configura la intensidad ambiental de la point light
	glUniform1f(glGetUniformLocation(program, "pointAmbientIntensity"), ambientIntensity);

	// Configura la intensidad difusa de la point light
	glUniform1f(glGetUniformLocation(program, "pointDiffuseIntensity"), diffuseIntensity);

	// Configura la posición de la point light
	glUniform3f(glGetUniformLocation(program, "pointPosition"), transform.position.x, transform.position.y, transform.position.z);

	// Configura el factor de atenuación constante de la point light
	glUniform1f(glGetUniformLocation(program, "pointConstant"), constant);

	// Configura el factor de atenuación lineal de la point light
	glUniform1f(glGetUniformLocation(program, "pointLinear"), linear);

	// Configura el factor de atenuación exponencial de la point light
	glUniform1f(glGetUniformLocation(program, "pointExponent"), exponent);
}

PointLight::~PointLight()
{
}

void PointLight::Update()
{
	// Incrementa el ángulo del ciclo día-noche según la velocidad y el tiempo transcurrido
	angle += speed * TIME_MANAGER.GetDeltaTime();

	// Normaliza el ángulo si excede el valor de dos veces pi
	if (angle > glm::two_pi<float>()) {
		angle -= glm::two_pi<float>();
	}

	// Calcula la posición de la entidad en la órbita circular
	transform.position.x = center.x + radius * cos(angle);
	transform.position.y = center.y + radius * sin(angle);
	transform.position.z = 0;

	// Calcula el factor de mezcla para transicionar entre el color del sol y la luna
	float blendFactor = (transform.position.y - center.y + radius) / (2.0f * radius);

	// Define los colores del sol y la luna
	glm::vec3 sunColor(1.0f, 1.0f, 0.0f);
	glm::vec3 moonColor(0.0f, 0.0f, 1.0f);

	// Mezcla entre los colores del sol y la luna basado en el factor de mezcla
	color = glm::mix(moonColor, sunColor, blendFactor);

	// Calcula el factor de intensidad basado en el factor de mezcla
	float intensityFactor = glm::mix(0.15f, 1.0f, blendFactor);

	// Ajusta la intensidad ambiental y difusa basada en el factor de intensidad
	ambientIntensity = ambientIntesityOriginal * intensityFactor;
	diffuseIntensity = diffuseIntesityOriginal * intensityFactor;
}

void PointLight::Render()
{
}
