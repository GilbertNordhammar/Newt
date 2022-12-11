#pragma once

#include "Jerboa/Rendering/Resource/Data/TextureData.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"
#include "Jerboa/Rendering/Resource/Config/TextureConfig.h"

#include "Jerboa/Core/Types.h"

#include <string>
#include <memory>

namespace Jerboa 
{
	class GPUResourceAllocator;

	class Texture2D
	{
	public:
		~Texture2D();
		void Create(const TextureConfig& config, GPUResourceAllocator& allocator);
		void CreateFromTextureData(const TextureData& data, TextureUsage usage, const GPUResourceAllocator& allocator);
		void UploadTextureData(const TextureData& data, const GPUResourceAllocator& allocator);

		const GPUResource&			GetGPUResouce() const { return m_TextureGPUResource; }
		const TextureConfig&		GetConfig() const { return m_Config; }
		TextureUsage				GetUsage() const { return m_Config.m_Usage; }
		PixelFormat					GetPixelFormat() const { return m_Config.m_PixelFormat; }
		uint32						GetWidth() const { return m_Config.m_Width; }
		uint32						GetHeight() const { return m_Config.m_Height; };
		TextureSamplingWrapMode		GetSamplerWrappingMode() const{ return m_Config.m_SamplerWrappingMode; }
		TextureSamplingFilter		GetSamplerFilter() const { return  m_Config.m_SamplingFilter; }
		MipmapInterpolationFilter	GetMipMapInterpolationFiler() const { return m_Config.m_MipMapInterpolationFilter; }
		bool						IsWriteable() const;
		bool						IsReadable() const;
		bool						IsColorTexture() const;
		bool						IsDepthTexture() const;
		bool						IsDepthStencilTexture() const;

	private:
		GPUResource m_TextureGPUResource;
		TextureConfig m_Config;
	};
}


