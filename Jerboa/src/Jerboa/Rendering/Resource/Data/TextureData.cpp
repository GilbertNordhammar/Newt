#include "jerboa-pch.h"
#include "TextureData.h"

#include "stb_image.h"

namespace Jerboa 
{
    TextureData::TextureData(unsigned char* data, uint32 width, uint32 height, PixelFormat pixelFormat, bool isHDR)
		: m_Data(data), m_Width(width), m_Height(height), m_PixelFormat(pixelFormat), m_IsHDR(isHDR)
	{
	}

	TextureData::~TextureData()
	{
		stbi_image_free(m_Data);
	}
}