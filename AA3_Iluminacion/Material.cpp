#include "Material.h"

Material::Material()
{
	diffuseIntensity = 0;
	specularIntensity = 0.f;
	shininess = 0.f;
}

Material::Material(GLfloat _diffuseIntensity, GLfloat _specularIntensity, GLfloat _shininess)
{
	diffuseIntensity = _diffuseIntensity;
	specularIntensity = _specularIntensity;
	shininess = _shininess;
}

void Material::UseMaterial(GLuint program)
{
	// Pasamos los uniforms al fragment shader
	glUniform1f(glGetUniformLocation(program, "materialDiffuseIntensity"), diffuseIntensity);
	glUniform1f(glGetUniformLocation(program, "materialSpecularIntensity"), specularIntensity);
	glUniform1f(glGetUniformLocation(program, "materialShininess"), shininess);
}

Material::~Material()
{
}
