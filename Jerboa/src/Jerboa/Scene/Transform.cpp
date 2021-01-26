#include "jerboa-pch.h"
#include "Transform.h"

#include "Jerboa/Debug.h";
#include "Jerboa/Debug.h"

#define GLM_ENABLE_EXPERIMENTAL

namespace Jerboa {
	Transform::Transform()
		: mPosition(glm::vec3(0)), mOrientation(glm::vec3(0))
	{
	}

	Transform::Transform(const glm::vec3& position)
		: mPosition(position), mOrientation(glm::vec3(0))
	{	
	}

	Transform::Transform(const glm::vec3& position, const glm::quat& mOrientation)
		: mPosition(position), mOrientation(mOrientation)
	{
	}

	Transform::Transform(const glm::vec3& position, float rotationAngle, const glm::vec3& rotationAxis)
		: mPosition(position), mOrientation(glm::angleAxis(rotationAngle, rotationAxis))
	{
	}

	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation)
		: mPosition(position), mOrientation(rotation)
	{
	}

	void Transform::Rotate(const glm::quat& mRotation)
	{
		mOrientation = mRotation * mOrientation;
	}

	void Transform::Rotate(const glm::vec3& rotation)
	{
		Rotate(glm::quat(rotation));
	}

	void Transform::Rotate(float angle, glm::vec3 axis)
	{
		float deviation = 0.0001;
		if (DecimalEquals(axis.x, 0, deviation) && DecimalEquals(axis.y, 0, deviation) && DecimalEquals(axis.z, 0, deviation))
			return;

		mOrientation = glm::rotate(mOrientation, angle, axis);
	}
}