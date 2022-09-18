#include "jerboa-pch.h"
#include "Texture.h"

#include "Jerboa/Core/EventBus.h"
#include "Jerboa/Rendering/Events/TextureDestroyedEvent.h"
#include "Jerboa/Debug.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa 
{
	Texture2D::~Texture2D()
	{
		EventBus::Publish(TextureDestroyedEvent(*this));
	}

	void Texture2D::Create(const TextureConfig& config, GPUResourceAllocator& allocator)
	{
		m_TextureGPUResource = allocator.CreateTexture(config);
		m_Config = config;
	}

	void Texture2D::CreateFromTextureData(const TextureData& data, TextureUsage usage, const GPUResourceAllocator& allocator)
	{
		m_Config.m_Usage = usage;
		m_Config.m_PixelFormat = data.GetPixelFormat();
		m_Config.m_Width = data.GetWidth();
		m_Config.m_Height = data.GetHeight();
		m_Config.m_SamplerWrappingMode = m_Config.m_PixelFormat == PixelFormat::RGBA ? TextureSamplingWrapMode::ClampToEdge : TextureSamplingWrapMode::Repeat;
		m_Config.m_SamplingFilter = TextureSamplingFilter::Linear;
		m_Config.m_MipMapInterpolationFilter = MipmapInterpolationFilter::Linear;

		m_TextureGPUResource = allocator.CreateTexture(m_Config);
		UploadTextureData(data, allocator);
	}

	void Texture2D::UploadTextureData(const TextureData& data, const GPUResourceAllocator& allocator)
	{
		JERBOA_ASSERT(m_TextureGPUResource.Get(), "Can't upload texture data since the texture gpu resource doesn't exist. Make sure that Texture2D::Create() has been called before.");
		if(m_Config.m_PixelFormat != data.GetPixelFormat())
			JERBOA_LOG_WARN("Texture doesn't have the same pixel format as the data being uploaded. The visual result might look wrong.");
		if (!m_TextureGPUResource.Get())
			return;

		GPUTextureResourceData gpuData;
		gpuData.m_Width = data.GetWidth();
		gpuData.m_Height = data.GetHeight();
		gpuData.m_PixelFormat = m_Config.m_PixelFormat;
		gpuData.m_PixelData = data.GetData();
		gpuData.m_GenerateMipmaps = true;
		allocator.UploadTextureData(m_TextureGPUResource, gpuData);
	}

	bool Texture2D::IsWriteable() const
	{
		return EnumHasFlags(m_Config.m_Usage, TextureUsage::Write);
	}

	bool Texture2D::IsReadable() const
	{
		return EnumHasFlags(m_Config.m_Usage, TextureUsage::Read);
	}
}

