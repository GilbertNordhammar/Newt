#include "jerboa-pch.h"
#include "Camera.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Core/Window.h"

namespace Jerboa {
	Camera::Camera(CameraType type, float fov)
		: Camera(glm::vec3(0), glm::quat(), type, fov)
	{
	}

	Camera::Camera(const glm::vec3& postion, CameraType type, float fov)
		: Camera(postion, glm::quat(), type, fov)
	{
	}

	Camera::Camera(const glm::vec3& postion, const glm::vec3& orientation, CameraType type, float fov)
		: Camera(postion, glm::quat(orientation), type, fov)
	{	
	}

	Camera::Camera(const glm::vec3& postion, const glm::quat& orientation, CameraType type, float fov)
		: mTransform(postion, orientation), mType(type), mFov(fov)
	{
	}

	const glm::mat4 Camera::GetViewMatrix() const
	{
		auto orientation = mTransform.GetOrientation();
		auto postion = mTransform.GetPosition();
		auto viewMatrix = glm::translate(glm::mat4(1.0), postion) * glm::toMat4(orientation);
		viewMatrix = glm::inverse(viewMatrix);
		return viewMatrix;
	}
	const glm::mat4 Camera::GetProjectionMatrix() const
	{
		return glm::perspective(mFov, Window::Get()->GetAspectRatio(), 0.1f, 100.0f);
	}
}