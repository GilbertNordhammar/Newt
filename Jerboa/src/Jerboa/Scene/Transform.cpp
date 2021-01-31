#include "jerboa-pch.h"
#include "Transform.h"

#include "Jerboa/Debug.h";
#include "Jerboa/Debug.h"

#define GLM_ENABLE_EXPERIMENTAL

namespace Jerboa {
	Transform::Transform()
		: Transform(glm::vec3(0), glm::quat())
	{
	}

	Transform::Transform(const glm::vec3& position)
		: Transform(position, glm::quat())
	{	
	}

	Transform::Transform(const glm::vec3& position, const glm::quat& orientation)
		: mPosition(position), mOrientation(glm::normalize(orientation))
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

	void Transform::Rotate(const glm::quat& rotation)
	{
		mOrientation = glm::normalize(rotation) * mOrientation;
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

	const glm::vec3 Transform::GetForward() const
	{
		return glm::rotate(mOrientation, GetWorldForward());;
	}

	const glm::vec3 Transform::GetUp() const
	{
		return glm::rotate(mOrientation, GetWorldUp());
	}

	const glm::vec3 Transform::GetRight() const
	{
		return glm::rotate(mOrientation, GetWorldRight());
	}
}