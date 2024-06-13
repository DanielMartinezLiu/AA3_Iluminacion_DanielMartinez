#pragma once

#include <GL/glew.h>

class Material
{
public:
	Material();

	Material(GLfloat _diffuseIntensity, GLfloat _specularIntensity, GLfloat _shininess);
	void UseMaterial(GLuint program);

	~Material();

private: 
	GLfloat diffuseIntensity;
	GLfloat specularIntensity;
	GLfloat shininess;

};

