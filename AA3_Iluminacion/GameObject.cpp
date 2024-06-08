#include "GameObject.h"

GameObject::GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _eyePosition, Model _model, Material _material, int _textureId)
{
	transform = Transform(_position, _rotation, _scale);

	eyePosition = _eyePosition;
	model = _model;
	material = _material;
	program = _program;
	textureId = _textureId;

	directionalLights = nullptr;
	pointLights = nullptr;
	spotLights = nullptr;
	directionalLightCount = 0;
	pointLightCount = 0;
	spotLightCount = 0;
}

void GameObject::Update()
{
	glUseProgram(program);

	glm::mat4 translationMatrix = Transform::GenerateTranslationMatrix(transform.position);
	glm::mat4 rotationMatrix = Transform::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
	rotationMatrix *= Transform::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
	rotationMatrix *= Transform::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
	glm::mat4 scaleMatrix = Transform::GenerateScaleMatrix(transform.scale);

	//Asignar valores iniciales al programa
	glUniform2f(glGetUniformLocation(program, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
	glUniform1i(glGetUniformLocation(program, "textureSampler"), textureId);

	// Pasar las matrices
	glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	glUniform1i(glGetUniformLocation(program, "usingTexture"), 1);

	glUniform3f(glGetUniformLocation(program, "eyePosition"), eyePosition.x, eyePosition.y, eyePosition.z);

	// Usar el material del objeto
	material.UseMaterial(program);

	// Pasar la luz direccional
	if (directionalLightCount > 0 && directionalLights)
	{
		SetDirectionalLights(directionalLights, directionalLightCount);
	}

	// Pasar la point light
	if (pointLightCount > 0 && pointLights)
	{
		SetPointLights(pointLights, pointLightCount);
	}

	// Pasar la spot light
	if (spotLightCount > 0 && spotLights)
	{
		SetSpotLights(spotLights, spotLightCount);
	}
}

void GameObject::Render()
{
	//Vinculo su VAO para ser usado
	glBindVertexArray(model.VAO);

	// Dibujamos
	glDrawArrays(GL_TRIANGLES, 0, model.numVertexs);

	//Desvinculamos VAO
	glBindVertexArray(0);
}
void GameObject::SetDirectionalLights(DirectionalLight* dLight, unsigned int lightCount)
{
	// Asignación de las luces direccionales y su cantidad
	directionalLights = dLight;
	directionalLightCount = lightCount;

	// Limitación de la cantidad de luces si excede el límite máximo
	if (lightCount > MAX_POINT_LIGHTS)
		lightCount = MAX_POINT_LIGHTS;

	// Envío del número actual de luces direccionales
	glUniform1i(glGetUniformLocation(program, "directionalLightCount"), lightCount);

	// Configuración de cada luz direccional
	for (size_t i = 0; i < lightCount; i++)
	{
		dLight[i].UseDirectionalLight(program, i);
	}
}
void GameObject::SetPointLights(PointLight* pLight, unsigned int lightCount)
{
	// Asignación de las point light y su cantidad
	pointLights = pLight;
	pointLightCount = lightCount;

	// Limitación de la cantidad de luces si excede el límite máximo
	if (lightCount > MAX_POINT_LIGHTS)
		lightCount = MAX_POINT_LIGHTS;

	// Envío del número actual las point light
	glUniform1i(glGetUniformLocation(program, "pointLightCount"), lightCount);

	// Configuración de cada point light
	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UsePointLight(program, i);
	}
}

void GameObject::SetSpotLights(SpotLight* sLight, unsigned int lightCount)
{
	// Asignación de las luces de foco y su cantidad
	spotLights = sLight;
	spotLightCount = lightCount;

	// Limitación de la cantidad de luces si excede el límite máximo
	if (lightCount > MAX_SPOT_LIGHTS)
		lightCount = MAX_SPOT_LIGHTS;

	// Envío del número actual las spot light
	glUniform1i(glGetUniformLocation(program, "spotLightCount"), lightCount);

	// Configuración de cada spot light
	for (size_t i = 0; i < lightCount; i++)
	{
		sLight[i].UseSpotLight(program, i);
	}
}