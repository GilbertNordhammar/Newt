#include "jerboa-pch.h"
#include "FrameBuffer.h"

#include "Jerboa/Debug.h"

namespace Jerboa
{
	void FrameBuffer::Create(const FrameBufferConfig& config, const GPUResourceAllocator& allocator)
	{
		FrameBufferGPUResourceConfig gpuConfig;

		for (int i = 0; i < config.m_ColorAttachments.size(); i++)
		{
			const Texture2D* colorTexture = config.m_ColorAttachments[i].GetTexture();
			
			if (!colorTexture)
				continue;

			const GPUResource& colorAttachmentGPU = colorTexture->GetGPUResouce();

			JERBOA_ASSERT(colorTexture->IsColorTexture(), "Texture has incompatible pixel format to be a color attachment");
			JERBOA_ASSERT(colorTexture->IsWriteable(), "Texture is not writeable and can therefore not be a color attachment");
			JERBOA_ASSERT(colorAttachmentGPU.Exists(), "Texture hasn't been allocated on GPU and can therefore not be a color attachment");

			const bool validColorAttachment = colorTexture->IsColorTexture() && colorTexture->IsWriteable() && colorAttachmentGPU.Exists();

			if (colorTexture->IsWriteable() && colorAttachmentGPU.Exists())
			{
				gpuConfig.m_ColorAttachments[i] = &colorAttachmentGPU;
				gpuConfig.m_ColorAttachmentsTextureConfig[i] = colorTexture->GetConfig();
			}
		}

		const Texture2D* depthStencilTexture = config.m_DepthStencilAttachment.GetTexture();
		if (depthStencilTexture)
		{
			const GPUResource& depthStencilAttachmentGPU = depthStencilTexture->GetGPUResouce();
			bool textureIsCompatibleForDepthStencil = depthStencilTexture->IsDepthStencilTexture() || depthStencilTexture->IsDepthTexture();

			bool validDepthStencilAttachment = textureIsCompatibleForDepthStencil && depthStencilTexture->IsWriteable() && depthStencilAttachmentGPU.Exists();

			JERBOA_ASSERT(textureIsCompatibleForDepthStencil, "Texture has incompatible pixel format for to be a depth + stencil attachment");
			JERBOA_ASSERT(depthStencilTexture->IsWriteable(), "Texture is not writeable and can therefore not be a depth + stencil attachment");
			if (depthStencilTexture->IsDepthStencilTexture())
			{
				JERBOA_ASSERT(!depthStencilTexture->IsReadable(), "Combined depth + stencil attachment cannot be readable");
				validDepthStencilAttachment &= !depthStencilTexture->IsReadable();
			}
			JERBOA_ASSERT(depthStencilAttachmentGPU.Exists(), "Texture hasn't been allocated on GPU and can therefore not be a depth + stencil attachment");

			JERBOA_ASSERT(validDepthStencilAttachment, "Invalid depth + stencil attachment!");
			if (validDepthStencilAttachment)
			{
				gpuConfig.m_DepthStencilAttachment = &depthStencilAttachmentGPU;
				gpuConfig.m_DepthStencilAttachmentTextureConfig = depthStencilTexture->GetConfig();
			}
		}
		
		m_GPUResource = allocator.CreateFrameBuffer(gpuConfig);
		m_Config = config;
	}

	const FrameBufferAttachment& FrameBuffer::GetColorAttachment(ColorAttachmentSlot slot) const
	{
		JERBOA_ASSERT(slot != ColorAttachmentSlot::Count, "ColorAttachmentSlot::Count is not a valid color attachment slot argument");
		return slot != ColorAttachmentSlot::Count 
			? m_Config.m_ColorAttachments[EnumToInt(slot)]
			: FrameBufferAttachment();
	}
}