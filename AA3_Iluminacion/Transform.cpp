#include "Transform.h"

glm::mat4 Transform::GenerateTranslationMatrix(glm::vec3 translation)
{
	return glm::translate(glm::mat4(1.f), translation);
}

glm::mat4 Transform::GenerateRotationMatrix(glm::vec3 axis, float fDegrees)
{
	return glm::rotate(glm::mat4(1.f), glm::radians(fDegrees), glm::normalize(axis));
}

glm::mat4 Transform::GenerateScaleMatrix(glm::vec3 _scale)
{
	return glm::scale(glm::mat4(1.f), _scale);
}