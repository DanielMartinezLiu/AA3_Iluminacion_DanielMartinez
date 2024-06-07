#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Light
{
public:
	Light();

	Light(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity,
		GLfloat _xDirection, GLfloat _yDirection, GLfloat _zDirection, GLfloat _diffuseIntensity);

	void UseLight(GLuint program);
	
	~Light();
private: 
	glm::vec3 color;
	GLfloat ambientIntensity;

	glm::vec3 direction;
	GLfloat diffuseIntensity;
};