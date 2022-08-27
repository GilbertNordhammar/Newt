#include "jerboa-pch.h"
#include "FrameBuffer.h"

#include "Jerboa/Debug.h"

namespace Jerboa
{
	FrameBuffer::FrameBuffer(std::vector<ColorAttachment>* colorAttachments, Texture2D* depthAttachment, Texture2D* stencilAttachment)
		: m_DepthAttachment(depthAttachment), m_StencilAttachment(stencilAttachment)
	{
		if (colorAttachments)
		{
			for (const auto& colorAttachment : *colorAttachments)
			{
				int index = EnumToInt<int>(colorAttachment.GetSlot());
				JERBOA_ASSERT(!m_ColorAttachments[index], "Color attachment slot " + std::to_string(index) + " already has a texture assigned");
				if (!m_ColorAttachments[index])
					m_ColorAttachments[index] = &colorAttachment.GetTexture();
			}
		}
	}

	const Texture2D* FrameBuffer::GetColorAttachment(ColorAttachmentSlot slot)
	{
		JERBOA_ASSERT(slot != ColorAttachmentSlot::Count, "ColorAttachmentSlot::Count is not a valid color attachment slot argument");
		return m_ColorAttachments[EnumToInt<int>(slot)];
	}
}