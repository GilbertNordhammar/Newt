#pragma once

#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/Types.h"
#include "Jerboa/Resource/Data/TextureData.h"

namespace Jerboa
{
	class TextureLoader
	{
	public:
		static TextureData LoadTexture(const char* path);
	};
}