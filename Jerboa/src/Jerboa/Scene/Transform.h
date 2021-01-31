#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Jerboa {
	class Transform
	{
	public:
		Transform();
		Transform(const glm::vec3& position);
		Transform(const glm::vec3& position, const glm::quat& orientation);
		Transform(const glm::vec3& position, float rotationAngle, const glm::vec3& rotationAxis);
		Transform(const glm::vec3& position, const glm::vec3& rotation);

		void Rotate(const glm::quat& rotation);
		void Rotate(const glm::vec3& rotation);
		void Rotate(float angle, glm::vec3 axis);
		//void RotateAround(glm::vec3 point, glm::vec3 axis, float angle); TBA

		void SetPosition(const glm::vec3& postion) { mPosition = postion; };
		void SetOrientation(const glm::quat& orientation) { mOrientation = glm::normalize(orientation); }
		void SetOrientation(const glm::vec3& orientationEuler) { mOrientation = glm::quat(orientationEuler); }

		glm::vec3 GetOrientationEuler() const { return glm::eulerAngles(mOrientation); }
		const glm::quat& GetOrientation() const { return mOrientation; }
		const glm::vec3& GetPosition() const { return mPosition; }
		
		const glm::vec3 GetForward() const;
		const glm::vec3 GetUp() const;
		const glm::vec3 GetRight() const;

		static glm::vec3 GetWorldForward() { return glm::vec3(0, 0, -1); }
		static glm::vec3 GetWorldUp() { return glm::vec3(0, 1, 0); }
		static glm::vec3 GetWorldRight() { return glm::vec3(1, 0, 0); }
	private:
		glm::vec3 mPosition;
		glm::quat mOrientation;
	};
}


