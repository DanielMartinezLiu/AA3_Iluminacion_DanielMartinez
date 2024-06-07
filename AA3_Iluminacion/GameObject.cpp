#include "GameObject.h"

GameObject::GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, Model _model, Light _light, int _textureId)
{
	transform = Transform(_position, _rotation, _scale);

	model = _model;
	program = _program;
	textureId = _textureId;
	light = _light;
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

	light.UseLight(program);
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


