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

			JERBOA_ASSERT(colorTexture->IsWriteable(), "Texture is not writeable and can therefore not be a color attachment");
			JERBOA_ASSERT(colorAttachmentGPU.Exists(), "Texture hasn't been allocated on GPU and can therefore not be a color attachment");

			if (colorTexture->IsWriteable() && colorAttachmentGPU.Exists())
			{
				
				m_ColorAttachments[i] = config.m_ColorAttachments[i];
				gpuConfig.m_ColorAttachments[i] = &colorAttachmentGPU;
				gpuConfig.m_ColorAttachmentsUsage[i] = colorTexture->GetUsage();
			}
		}

		const Texture2D* depthTexture = config.m_DepthAttachment.GetTexture();
		if (depthTexture)
		{
			const GPUResource& depthAttachmentGPU = depthTexture->GetGPUResouce();
			JERBOA_ASSERT(depthTexture->IsWriteable(), "Texture is not writeable and can therefore not be a depth attachment");
			JERBOA_ASSERT(depthAttachmentGPU.Exists(), "Texture hasn't been allocated on GPU and can therefore not be a depth attachment");
			if (depthTexture->IsWriteable() && depthAttachmentGPU.Exists())
			{
				m_DepthAttachment = config.m_DepthAttachment;
				gpuConfig.m_DepthAttachment = &depthAttachmentGPU;
				gpuConfig.m_DepthAttachmentUsage = depthTexture->GetUsage();
			}
		}

		const Texture2D* stencilTexture = config.m_StencilAttachment.GetTexture();
		if (stencilTexture)
		{
			const GPUResource& stencilAttachmentGPU = stencilTexture->GetGPUResouce();

			JERBOA_ASSERT(stencilTexture->IsWriteable(), "Texture is not writeable and can therefore not be a stencil attachment");
			JERBOA_ASSERT(stencilAttachmentGPU.Exists(), "Texture hasn't been allocated on GPU and can therefore not be a depth attachment");
			if (stencilTexture->IsWriteable() && stencilAttachmentGPU.Exists())
			{
				m_StencilAttachment = config.m_StencilAttachment;
				gpuConfig.m_StencilAttachment = &stencilAttachmentGPU;
				gpuConfig.m_StencilAttachmentUsage = stencilTexture->GetUsage();
			}
		}
		
		m_GPUResource = allocator.CreateFrameBuffer(gpuConfig);
	}

	const FrameBufferAttachment& FrameBuffer::GetColorAttachment(ColorAttachmentSlot slot) const
	{
		JERBOA_ASSERT(slot != ColorAttachmentSlot::Count, "ColorAttachmentSlot::Count is not a valid color attachment slot argument");
		return slot != ColorAttachmentSlot::Count 
			? m_ColorAttachments[EnumToInt<int>(slot)]
			: FrameBufferAttachment();
	}
}