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

private:
	std::vector<GLfloat> points;
	glm::vec4 color;

	GLuint vao;
	GLuint vbo;

	Material material;
	DirectionalLight light;

	unsigned int directionalLightCount;
	DirectionalLight* directionalLights;

	unsigned int pointLightCount;
	PointLight* pointLights;

	unsigned int spotLightCount;
	SpotLight* spotLights;
public:
	Primitive(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color);

	void InitPrimitive();

	void Update() override;
	void Render() override;
};

