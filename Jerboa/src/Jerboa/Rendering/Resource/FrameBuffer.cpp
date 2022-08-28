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
			std::shared_ptr<Texture2D> texture = config.m_ColorAttachments[i];

			if (!texture)
				continue;

			const GPUResource& colorAttachmentGPU = texture->GetGPUResouce();

			JERBOA_ASSERT(texture->IsWriteable(), "Texture is not writeable and can therefore not be a color attachment");
			JERBOA_ASSERT(colorAttachmentGPU.Exists(), "Texture hasn't been allocated on GPU and can therefore not be a color attachment");

			if (texture->IsWriteable() && colorAttachmentGPU.Exists())
			{
				m_ColorAttachments[i] = texture;
				gpuConfig.m_ColorAttachments[i] = &colorAttachmentGPU;
				gpuConfig.m_ColorAttachmentsUsage[i] = texture->GetUsage();
			}
		}

		std::shared_ptr<Texture2D> depthAttachment = config.m_DepthAttachment;
		if (depthAttachment)
		{
			const GPUResource& depthAttachmentGPU = depthAttachment->GetGPUResouce();
			JERBOA_ASSERT(depthAttachment->IsWriteable(), "Texture is not writeable and can therefore not be a depth attachment");
			JERBOA_ASSERT(depthAttachmentGPU.Exists(), "Texture hasn't been allocated on GPU and can therefore not be a depth attachment");
			if (depthAttachment->IsWriteable() && depthAttachmentGPU.Exists())
			{
				m_DepthAttachment = depthAttachment;
				gpuConfig.m_DepthAttachment = &depthAttachmentGPU;
				gpuConfig.m_DepthAttachmentUsage = depthAttachment->GetUsage();
			}
		}

		std::shared_ptr<Texture2D> stencilAttachment = config.m_StencilAttachment;
		if (stencilAttachment)
		{
			const GPUResource& stencilAttachmentGPU = stencilAttachment->GetGPUResouce();

			JERBOA_ASSERT(stencilAttachment->IsWriteable(), "Texture is not writeable and can therefore not be a stencil attachment");
			JERBOA_ASSERT(stencilAttachmentGPU.Exists(), "Texture hasn't been allocated on GPU and can therefore not be a depth attachment");
			if (stencilAttachment->IsWriteable() && stencilAttachmentGPU.Exists())
			{
				m_StencilAttachment = stencilAttachment;
				gpuConfig.m_StencilAttachment = &stencilAttachmentGPU;
				gpuConfig.m_StencilAttachmentUsage = stencilAttachment->GetUsage();
			}
		}
		
		m_GPUResource = allocator.CreateFrameBuffer(gpuConfig);
	}

	const Texture2D* FrameBuffer::GetColorAttachment(ColorAttachmentSlot slot)
	{
		JERBOA_ASSERT(slot != ColorAttachmentSlot::Count, "ColorAttachmentSlot::Count is not a valid color attachment slot argument");
		return slot != ColorAttachmentSlot::Count 
			? m_ColorAttachments[EnumToInt<int>(slot)].get()
			: nullptr;
	}
}