#include "Material.h"

Material::Material()
{
	specularIntensity = 0.f;
	shininess = 0.f;
}

Material::Material(GLfloat _specularIntensity, GLfloat _shininess)
{
	specularIntensity = _specularIntensity;
	shininess = _shininess;
}

void Material::UseMaterial(GLuint program)
{
	glUniform1f(glGetUniformLocation(program, "material.specularIntensity"), specularIntensity);
	glUniform1f(glGetUniformLocation(program, "material.shininess"), shininess);
}

Material::~Material()
{
}