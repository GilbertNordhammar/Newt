#pragma once

#include "Jerboa/Core/Event.h"
#include "Jerboa/Rendering/Resource/Shader.h"

namespace Jerboa {
	struct ShaderDestroyedEvent : Event 
	{
		ShaderDestroyedEvent(const Shader& shader)
			: m_Shader(shader)
		{
		}

		const Shader& m_Shader;
	};
}