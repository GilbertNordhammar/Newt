#pragma once

namespace Jerboa
{
	enum class TextureUsage
	{
		None, Read, Write, ReadWrite
	};

	struct TextureConfig
	{
		TextureUsage m_Usage;
		PixelFormat m_PixelFormat;
		uint32 m_Width;
		uint32 m_Height;
	};
}