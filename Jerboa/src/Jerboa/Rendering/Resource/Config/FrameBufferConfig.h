#pragma once

#include "Jerboa/Rendering/Resource/Texture.h"

#include <memory>

namespace Jerboa
{
	class Texture2D;

	enum class ColorAttachmentSlot
	{
		S0 = 0, S1, S2, S3, S4, S5, S6, S7, Count
	};

	class ColorAttachment
	{
		ColorAttachment(ColorAttachmentSlot slot, std::shared_ptr<Texture2D> texture)
			: m_Slot(slot), m_Texture(texture)
		{
		}

	public:
		ColorAttachmentSlot GetSlot() const { return m_Slot; }
		std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }

	private:
		ColorAttachmentSlot m_Slot = ColorAttachmentSlot::S0;
		std::shared_ptr<Texture2D> m_Texture;
	};

	struct FrameBufferConfig
	{
		std::array<std::shared_ptr<Texture2D>, EnumToInt<int>(ColorAttachmentSlot::Count)> m_ColorAttachments;
		std::shared_ptr<Texture2D> m_DepthAttachment;
		std::shared_ptr<Texture2D> m_StencilAttachment;
	};
}