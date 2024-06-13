#include "GameObject.h"

GameObject::GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _eyePosition, Model _model, Material _material, int _textureId)
{
	transform = Transform(_position, _rotation, _scale);

	eyePosition = _eyePosition;
	model = _model;
	material = _material;
	program = _program;
	textureId = _textureId;

	directionalLight = nullptr;
	pointLight = nullptr;
	spotLight = nullptr;
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
	if (directionalLight != nullptr)
	{
		directionalLight->UseDirectionalLight(program);
	}
	// Pasar la point light
	if (pointLight != nullptr)
	{
		pointLight->UsePointLight(program);
	}
	// Pasar la spot light
	if (spotLight != nullptr)
	{
		spotLight->UseSpotLight(program);
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

void GameObject::SetLights(DirectionalLight* dLight, PointLight* pLight, SpotLight* sLight)
{
	directionalLight = dLight;
	pointLight = pLight;
	spotLight = sLight;
}
