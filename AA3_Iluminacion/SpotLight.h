#pragma once

#include "PointLight.h"

class SpotLight : public PointLight
{
public:
	SpotLight();

	SpotLight(
		GLfloat _red, GLfloat _green, GLfloat _blue,
		GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
		GLfloat _xPos, GLfloat _yPos, GLfloat _zPos,
		GLfloat _xDir, GLfloat _yDir, GLfloat _zDir,
		GLfloat _constant, GLfloat _linear, GLfloat _exponent,
		GLfloat _edge);

	void UseSpotLight(GLuint program, int index);

	void SetCamera(Camera* _camera);

	void Update() override;
	void Render() override;

	void KeyControl(bool* keys);

	~SpotLight();

private:
	Camera* camera;
	glm::vec3 direction;

	GLfloat ambientIntensityOriginal;

	GLfloat edge;
	GLfloat procEdge;
	
	bool lightActive;
	bool isPressing;
};

