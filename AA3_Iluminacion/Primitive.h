#pragma once
#include <gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <vector>

#include "Entity.h"
#include "GLManager.h"

class Primitive : public Entity
{

private:
	std::vector<GLfloat> points;
	glm::vec4 color;

	GLuint vao;
	GLuint vbo;

public:
	Primitive(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, Light _light);

	void InitPrimitive();
	void Update() override;
	void Render() override;
};

