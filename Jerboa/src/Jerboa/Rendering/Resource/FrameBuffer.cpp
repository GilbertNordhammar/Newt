#include "jerboa-pch.h"
#include "FrameBuffer.h"

#include "Jerboa/Debug.h"

namespace Jerboa
{
	void FrameBuffer::Create(const FrameBufferConfig& config)
	{
		for (int i = 0; i < config.m_ColorAttachments.size(); i++)
		{
			std::shared_ptr<Texture2D> texture = config.m_ColorAttachments[i];
			if (!texture)
				continue;

			JERBOA_ASSERT(!m_ColorAttachments[i], "Color attachment at slot " + std::to_string(i) + " is assigned twice");
			JERBOA_ASSERT(texture->IsWriteable(), "Texture is not writeable and can therefore not be a color attachment");

			if (!m_ColorAttachments[i] && texture->IsWriteable())
				m_ColorAttachments[i] = texture;
		}

		std::shared_ptr<Texture2D> depthAttachment = config.m_DepthAttachment;
		if (depthAttachment)
		{
			JERBOA_ASSERT(depthAttachment->IsWriteable(), "Texture is not writeable and can therefore not be a depth attachment");
			if (depthAttachment->IsWriteable())
			{
				m_DepthAttachment = depthAttachment;
			}
		}

		std::shared_ptr<Texture2D> stencilAttachment = config.m_StencilAttachment;
		if (stencilAttachment)
		{
			JERBOA_ASSERT(stencilAttachment->IsWriteable(), "Texture is not writeable and can therefore not be a stencil attachment");
			if (stencilAttachment->IsWriteable())
			{
				m_StencilAttachment = stencilAttachment;
			}
		}
	}

	const Texture2D* FrameBuffer::GetColorAttachment(ColorAttachmentSlot slot)
	{
		JERBOA_ASSERT(slot != ColorAttachmentSlot::Count, "ColorAttachmentSlot::Count is not a valid color attachment slot argument");
		return slot != ColorAttachmentSlot::Count 
			? m_ColorAttachments[EnumToInt<int>(slot)].get()
			: nullptr;
	}
}