#pragma once
#include <gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <vector>

#include "Entity.h"
#include "GLManager.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "CommonValues.h"

class Primitive : public Entity
{
public:
	Primitive(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, glm::vec3 _eyePosition, Material _material);
	Primitive(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, glm::vec3 _eyePosition, Material _material, GLfloat _radius, GLfloat _speed, GLfloat _angle, bool _orbitObject);

	void InitPrimitive();

	void Update() override;
	void Render() override;

	void UpdateOrbit();

	void SetDirectionalLights(DirectionalLight* dLight, unsigned int lightCount);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount);

private:
	glm::vec3 eyePosition;

	std::vector<GLfloat> points;
	glm::vec4 color;

	GLuint vao;
	GLuint vbo;

	Material material;

	unsigned int directionalLightCount;
	DirectionalLight* directionalLights;

	unsigned int pointLightCount;
	PointLight* pointLights;

	unsigned int spotLightCount;
	SpotLight* spotLights;

	glm::vec3 center;
	float radius;
	float speed;
	float angle;
	
	bool orbitObject;
};

