#pragma once

#include "BaseLight.h"

#include <glm/glm.hpp>

namespace Jerboa {
	class PointLight : public BaseLight {
	public:
		PointLight(glm::vec3 color, float power, glm::vec3 position)
			: BaseLight(color, power), Position(position)
		{
		}

		glm::vec3 Position;
	};
}