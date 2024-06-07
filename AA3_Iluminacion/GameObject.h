#pragma once

#include "Model.h"
#include "Entity.h"
#include "GLManager.h"
#include "Light.h"

class GameObject : public Entity
{
public:
	GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, Model _model, Light _light, int _textureId);

	void CalculateAverageNormals(unsigned int* indices, unsigned int indiceCount, unsigned int* vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);

	void Update() override;
	void Render() override;

private:
	Model model;
	int textureId;
};