#include "jerboa-pch.h"
#include "Texture.h"

#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Platform/OpenGL/OpenGL_Texture2D.h"

#include "Jerboa/Debug.h"

namespace Jerboa {
	std::shared_ptr<Texture2D> Jerboa::Texture2D::Create(const std::string& path, TextureType type)
	{
		std::shared_ptr<Texture2D> texture;

		switch (Platform::GetRenderApi()) {
			case RenderAPI::OpenGL:
				texture = std::make_shared<OpenGL_Texture2D>(path, type);
		}


		JERBOA_ASSERT(texture, "Implementation is missing or render API is not set");
		return texture;
	}
}

