#pragma once

#include "Jerboa/Rendering/GPUResource.h"
#include "Jerboa/Resource/Data/TextureData.h"
#include "Jerboa/Core/Types.h"

#include <string>
#include <memory>

namespace Jerboa {
	class GPUResourceAllocator;

	class Texture
	{
	public:
		virtual int_fast32_t GetWidth() const = 0;
		virtual int_fast32_t GetHeight() const = 0;
		virtual const std::string& GetPath() const = 0;
		virtual void Bind(int slot) = 0;
	};

	enum class TextureType 
	{
		Albedo, Normal, Metallic, Roughness, AmbientOcclusion
	};

	class Texture2D
	{
	public:
		void Create(TextureType type, const TextureData& data, GPUResourceAllocator& allocator);

		const GPUResource&	GetGPUResouce() const { return m_TextureResource; }
		uint32				GetWidth() const { return m_Width; }
		uint32				GetHeight() const { return m_Height; };
		TextureType			GetType() const { return m_Type; }
		PixelFormat			GetPixelFormat() const { return m_PixelFormat; }

	private:
		GPUResource m_TextureResource;
		uint32		m_Width;
		uint32		m_Height;
		TextureType m_Type;
		PixelFormat m_PixelFormat;
	};
}


