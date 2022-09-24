#pragma once

#include "Jerboa/Core/Enum.h"

namespace Jerboa
{
	enum class TextureUsage
	{
		Read = 1,
		Write = 2
	};

	JERBOA_ENABLE_ENUM_FLAG_OPERATORS(TextureUsage)
	

	enum class TextureSamplingFilter
	{
		Nearest, Linear
	};

	enum class MipmapInterpolationFilter
	{
		None, Nearest, Linear
	};

	enum class TextureSamplingWrapMode
	{
		Repeat, ClampToEdge, MirrorRepeat
	};

	struct TextureConfig
	{
		TextureUsage				m_Usage = TextureUsage::Read;
		PixelFormat					m_PixelFormat = PixelFormat::None;
		uint32						m_Width = 0;
		uint32						m_Height = 0;
		TextureSamplingWrapMode		m_SamplerWrappingMode = TextureSamplingWrapMode::Repeat;
		TextureSamplingFilter		m_SamplingFilter = TextureSamplingFilter::Linear;
		MipmapInterpolationFilter	m_MipMapInterpolationFilter = MipmapInterpolationFilter::None;
	};
}