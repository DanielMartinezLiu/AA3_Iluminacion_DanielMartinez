#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "Material.h"
#include "Camera.h"

class Light
{
public:
	Light();

	Light(
		GLfloat _red, GLfloat _green, GLfloat _blue, 
		GLfloat _ambientIntensity, GLfloat _diffuseIntensity);
	~Light();

protected: 
	glm::vec3 eyePosition;

	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

};