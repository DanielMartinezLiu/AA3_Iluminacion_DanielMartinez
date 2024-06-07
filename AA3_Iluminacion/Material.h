#pragma once

#include <GL/glew.h>

class Material
{
public:
	Material();

	Material(GLfloat _specularIntensity, GLfloat _shininess);
	void UseMaterial(GLuint program);

	~Material();

private: 
	GLfloat specularIntensity;
	GLfloat shininess;

};

