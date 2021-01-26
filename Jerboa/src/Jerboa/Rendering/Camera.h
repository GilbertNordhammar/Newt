#pragma once

#include "Jerboa/Scene/Transform.h"

#include "Jerboa/Core/Base.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace Jerboa {
	enum class CameraType {
		Orthographic, Perspective
	};

	class Camera
	{
	public:
		Camera(CameraType type, float fov);
		Camera(const glm::vec3& postion, CameraType type, float fov);
		Camera(const glm::vec3& postion, const glm::vec3& orientation, CameraType type, float fov);
		Camera(const glm::vec3& postion, const glm::quat& orientation, CameraType type, float fov);

		// Clamped to [0, pi)
		void SetFov(float fov) { fov = std::clamp(fov, 0.0f, glm::pi<float>() - 0.0001f); };
		
		const glm::mat4 GetViewMatrix() const;
		const glm::mat4 GetProjectionMatrix() const;
		CameraType GetType() const { return mType; }
		Transform& GetTransform() { return mTransform; }
		
	private:
		Transform mTransform;
		CameraType mType;
		float mFov;
	};

}


