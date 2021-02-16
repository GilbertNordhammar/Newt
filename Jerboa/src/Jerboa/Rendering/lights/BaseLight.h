#pragma once

#include "Jerboa/Debug.h"

#include <glm/glm.hpp>

namespace Jerboa {
	class BaseLight {
	public:
		// Gets clamped to [0, 1]
		void SetColor(const glm::vec3& color) { mColor = glm::clamp(color, glm::vec3(0), glm::vec3(1)); }
		// Gets clamped to [0, infinity]
		void SetPower(float power) { mPower = glm::max(0.0f, power); }

		glm::vec3 GetColor() const { return mColor; }
		float GetPower() const { return mPower; }
	protected:
		BaseLight(const glm::vec3& color, float power)
			: mColor(color), mPower(power)
		{
		}

		glm::vec3 mColor;
		float mPower;
	};
}