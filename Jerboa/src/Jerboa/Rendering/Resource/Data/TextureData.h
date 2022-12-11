#pragma once

#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/Types.h"

namespace Jerboa
{
    class TextureData
	{
	public:
		TextureData(unsigned char* data, uint32 width, uint32 height, PixelFormat pixelFormat, bool isHDR);
		~TextureData();

		uint32 GetWidth() const { return m_Width; }
		uint32 GetHeight() const{ return m_Height; }
		unsigned char* GetData() const{ return m_Data; }
		PixelFormat GetPixelFormat() const { return m_PixelFormat; }
		uint32 GetSize() { return m_Width * m_Height; }
		bool IsHDR() { return m_IsHDR; }
		bool IsValid() { return m_Data && m_PixelFormat != PixelFormat::None; }

	private:
		uint32 m_Width;
		uint32 m_Height;
		unsigned char* m_Data = nullptr;
		PixelFormat m_PixelFormat;
		bool m_IsHDR;
	};
}