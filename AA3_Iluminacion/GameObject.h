#pragma once

#include "Model.h"
#include "Entity.h"
#include "GLManager.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "CommonValues.h"

class GameObject : public Entity
{
public:

	GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _eyePosition, Model _model, Material _material, int _textureId);

	void SetLights(DirectionalLight* dLight, PointLight* pLight, SpotLight* sLight);

	void Update() override;
	void Render() override;

private:
	glm::vec3 eyePosition;
	Model model;
	Material material;

	DirectionalLight* directionalLight;
	PointLight* pointLight;
	SpotLight* spotLight;

	int textureId;
};