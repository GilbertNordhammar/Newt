#include "jerboa-pch.h"
#include "TextureLoader.h"

#include "Jerboa/Debug.h"

#include "stb_image.h"
#include <string>

namespace Jerboa
{
	TextureData TextureLoader::LoadTexture(const char* path)
	{
#if defined(JERBOA_RENDER_API_OPENGL)
		stbi_set_flip_vertically_on_load(true);
#endif
		int width, height;
		int nColorChannels;
		unsigned char* data{};
		bool isHDR = stbi_is_hdr(path); // TODO: Can HDR be checked after texture is loaded? Doesn't seem very efficient to read from disk twice

		if (isHDR)
			JERBOA_LOG_INFO("Loading HDR texture \"{0}\"", path);
		else
			JERBOA_LOG_INFO("Loading texture \"{0}\"", path);

		// TODO: Consider using stbi_loadf for HDR textures since it keeps HDR colors
		data = stbi_load(path, &width, &height, &nColorChannels, 0);
		if(!data)
			JERBOA_LOG_ERROR("Couldn't load texture {0}", path);

		PixelFormat pixelFormat = PixelFormat::None;
		switch (nColorChannels)
		{
			case 1:
				pixelFormat = PixelFormat::Red;
				break;
			case 3:
				pixelFormat = PixelFormat::RGB;
				break;
			case 4:
				pixelFormat = PixelFormat::RGBA;
				break;
			default:
				std::string errorMessage = "No handling of " + std::to_string(nColorChannels) + " color channels";
				JERBOA_ASSERT(false, errorMessage)
		}

		if(!data)
			return TextureData(nullptr, 0, 0, PixelFormat::None, false);

		return TextureData(data, static_cast<uint32>(width), static_cast<uint32>(height), pixelFormat, isHDR);
	}
	
}