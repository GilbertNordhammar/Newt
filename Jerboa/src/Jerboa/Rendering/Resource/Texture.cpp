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
		m_Width = config.m_Width;
		m_Height = config.m_Height;
		m_PixelFormat = config.m_PixelFormat;
		m_Usage = config.m_Usage;
	}

	void Texture2D::CreateFromTextureData(const TextureData& data, TextureUsage usage, const GPUResourceAllocator& allocator)
	{
		m_Width = data.GetWidth();
		m_Height = data.GetHeight();
		m_PixelFormat = data.GetPixelFormat();
		m_Usage = usage;

		TextureConfig config;
		config.m_Width = m_Width;
		config.m_Height = m_Height;
		config.m_PixelFormat = m_PixelFormat;
		m_TextureGPUResource = allocator.CreateTexture(config);
		UploadTextureData(data, allocator);
	}

	void Texture2D::UploadTextureData(const TextureData& data, const GPUResourceAllocator& allocator)
	{
		JERBOA_ASSERT(m_TextureGPUResource.Get(), "Can't upload texture data since the texture gpu resource doesn't exist. Make sure that Texture2D::Create() has been called before.");
		JERBOA_ASSERT(m_PixelFormat == data.GetPixelFormat(), "Texture doesn't have the same pixel format as the data being uploaded. The visual result might look wrong");
		if (!m_TextureGPUResource.Get())
			return;

		allocator.UploadTextureData(m_TextureGPUResource, data);
	}
}

