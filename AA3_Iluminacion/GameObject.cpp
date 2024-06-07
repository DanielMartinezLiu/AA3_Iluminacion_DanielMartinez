#include "GameObject.h"

GameObject::GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, Model _model, Light _light, int _textureId)
{
	transform = Transform(_position, _rotation, _scale);

	model = _model;
	program = _program;
	textureId = _textureId;
	light = _light;
}

void GameObject::CalculateAverageNormals(unsigned int* indices, unsigned int indiceCount, unsigned int* vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; 
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}
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


