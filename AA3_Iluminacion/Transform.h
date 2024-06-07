#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Transform
{

public:
	Transform() = default;
	Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale):
		position(_position), rotation(_rotation), scale(_scale){}


	glm::vec3 position, rotation, scale;

	static glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);
	static glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	static glm::mat4 GenerateScaleMatrix(glm::vec3 _scale);
};

