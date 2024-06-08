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

	void Update() override;
	void Render() override;

	void SetDirectionalLights(DirectionalLight* dLight, unsigned int lightCount);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount);

private:
	glm::vec3 eyePosition;
	Model model;
	Material material;

	unsigned int directionalLightCount;
	DirectionalLight* directionalLights;

	unsigned int pointLightCount;
	PointLight* pointLights;

	unsigned int spotLightCount;
	SpotLight* spotLights;

	int textureId;
};