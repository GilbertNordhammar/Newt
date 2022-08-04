#pragma once

#include "Jerboa/Core/Event.h"
#include "Jerboa/Rendering/Resource/Texture.h"

namespace Jerboa {
	struct TextureDestroyedEvent : Event 
	{
		TextureDestroyedEvent(const Texture2D& texture)
			: m_Texture(texture)
		{
		}

		const Texture2D& m_Texture;
	};
}