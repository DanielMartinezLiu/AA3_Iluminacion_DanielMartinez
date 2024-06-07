#pragma once

#include "Model.h"
#include "Entity.h"
#include "GLManager.h"
#include "DirectionalLight.h"

class GameObject : public Entity
{
public:

	GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _eyePosition, Model _model, Material _material, DirectionalLight _light, int _textureId);

	void Update() override;
	void Render() override;

private:
	glm::vec3 eyePosition;
	Model model;
	Material material;
	DirectionalLight light;

	int textureId;
};